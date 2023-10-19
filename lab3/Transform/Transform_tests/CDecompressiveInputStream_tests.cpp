#include "../Transform/CDecompressiveInputStream.h"
#include "../../../external/catch2/catch.hpp"
#include <fstream>
#include "../Transform/CFileInputStream.h"


SCENARIO("Decompressive input stream tests")
{
	GIVEN("Decompressive input stream with one byte")
	{
		std::ofstream ofstrm("test.dat", std::ofstream::out | std::ofstream::binary);
		ofstrm << "1A";
		ofstrm.close();
		IInputPtr strm = std::make_unique<CFileInputStream>("test.dat");
		CDecompressiveInputStream decompStrm(std::move(strm));

		THEN("Can read byte from decompressive stream")
		{
			CHECK(decompStrm.ReadByte() == 'A');
		}

		THEN("Can read block from decompressive stream")
		{
			char* buffer = new char[1];
			CHECK(decompStrm.ReadBlock(buffer, 2) == 1);
			CHECK(*buffer == 'A');
			delete[] buffer;
		}
	}

	GIVEN("Decompressive input stream with three similar bytes")
	{
		std::ofstream ofstrm("test.dat", std::ofstream::out | std::ofstream::binary);
		ofstrm << "3A";
		ofstrm.close();
		IInputPtr strm = std::make_unique<CFileInputStream>("test.dat");
		CDecompressiveInputStream decompStrm(std::move(strm));

		THEN("Can read byte from decompressive stream")
		{
			CHECK(decompStrm.ReadByte() == 'A');
		}

		THEN("Can read full block from decompressive stream")
		{
			char* buffer = new char[3];
			CHECK(decompStrm.ReadBlock(buffer, 3) == 3);
			CHECK(strncmp(buffer, "AAA", 3) == 0);
			delete[] buffer;
		}

		THEN("Can read the part of the block from decompressive stream")
		{
			char* buffer = new char[2];
			REQUIRE(decompStrm.ReadBlock(buffer, 2) == 2);
			CHECK(strncmp(buffer, "AA", 2) == 0);
			delete[] buffer;
		}
	}

	GIVEN("Decompressive input stream with different bytes")
	{
		std::ofstream ofstrm("test.dat", std::ofstream::out | std::ofstream::binary);
		ofstrm << "3A2B1C";
		ofstrm.close();
		IInputPtr strm = std::make_unique<CFileInputStream>("test.dat");
		CDecompressiveInputStream decompStrm(std::move(strm));

		THEN("Can read byte from decompressive stream")
		{
			CHECK(decompStrm.ReadByte() == 'A');
		}

		THEN("Can read full block from decompressive stream")
		{
			char* buffer = new char[6];
			CHECK(decompStrm.ReadBlock(buffer, 6) == 6);
			CHECK(strncmp(buffer, "AAABBC", 6) == 0);
			delete[] buffer;
		}

		WHEN("Try to read block greater than file")
		{
			char* buffer = new char[7];
			CHECK(decompStrm.ReadBlock(buffer, 7) == 6);

			THEN("Full file was decompressed")
			{
				CHECK(strncmp(buffer, "AAABBC", 6) == 0);
				delete[] buffer;
			}
		}

		WHEN("Read stream by byte")
		{
			std::vector<uint8_t> expectedBytes = { 'A', 'A', 'A', 'B', 'B', 'C' };

			THEN("Bytes was decompressed")
			{
				for (int i = 0; i < 6; i++)
				{
					CHECK(decompStrm.ReadByte() == expectedBytes[i]);
				}
			}
		}

		WHEN("Read by byte, then read block")
		{
			char* buffer = new char[4];

			THEN("Bytes was decompressed")
			{
				CHECK(decompStrm.ReadByte() == 'A');
				CHECK(decompStrm.ReadByte() == 'A');
				CHECK(decompStrm.ReadBlock(buffer, 4) == 4);
				CHECK(strncmp(buffer, "ABBC", 4) == 0);
				delete[] buffer;
			}
		}
	}
}
