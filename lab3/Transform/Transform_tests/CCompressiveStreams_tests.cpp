#include "../../../external/catch2/catch.hpp"
#include "../Transform/CCompressiveOutputStream.h"
#include "../Transform/CDecompressiveInputStream.h"
#include "../Transform/CMemoryInputStream.h"
#include "../Transform/CMemoryOutputStream.h"
#include "../Transform/IDataStreams.h"

namespace
{
	bool operator==(std::vector<uint8_t> const& left, std::string const& right)
	{
		if (left.size() != right.size())
		{
			return false;
		}

		for (size_t i = 0; i < left.size(); i++)
		{
			if (left[i] != right[i])
			{
				return false;
			}
		}

		return true;
	}
}

SCENARIO("Compressive output stream tests")
{
	GIVEN("Compressive output stream")
	{
		std::vector<uint8_t> v;
		IOutputPtr outStrm = std::make_unique<CMemoryOutputStream>(v);
		CCompressiveOutputStream compStrm(std::move(outStrm));

		WHEN("Write single byte")
		{
			compStrm.WriteByte('A');
			compStrm.Flush();

			THEN("Byte was compressed and can be decompressed")
			{
				IInputPtr inStrm = std::make_unique<CMemoryInputStream>(v);
				CDecompressiveInputStream decompStrm(std::move(inStrm));
				CHECK(decompStrm.ReadByte() == 'A');
			}
		}

		WHEN("Write data by bytes")
		{
			compStrm.WriteByte('A');
			compStrm.WriteByte('A');
			compStrm.WriteByte('A');
			compStrm.WriteByte('B');
			compStrm.WriteByte('B');
			compStrm.Flush();

			THEN("Byte was compressed")
			{
				IInputPtr inStrm = std::make_unique<CMemoryInputStream>(v);
				CDecompressiveInputStream decompStrm(std::move(inStrm));
				std::string str;
				REQUIRE(decompStrm.ReadBlock(str.data(), 5) == 5);
				CHECK(strncmp(str.c_str(), "AAABB", 5) == 0);
			}
		}

		WHEN("Write data block")
		{
			compStrm.WriteBlock("AAABBC", 6);
			compStrm.Flush();

			THEN("Byte was compressed")
			{
				IInputPtr inStrm = std::make_unique<CMemoryInputStream>(v);
				CDecompressiveInputStream decompStrm(std::move(inStrm));
				std::string str;
				REQUIRE(decompStrm.ReadBlock(str.data(), 6) == 6);
				CHECK(strncmp(str.c_str(), "AAABBC", 6) == 0);
			}
		}

		WHEN("Write data block greater than 8 bytes")
		{
			compStrm.WriteBlock("AAAAAAAAAA", 10);
			compStrm.Flush();

			THEN("Bytes was compressed in two blocks")
			{
				IInputPtr inStrm = std::make_unique<CMemoryInputStream>(v);
				CDecompressiveInputStream decompStrm(std::move(inStrm));
				std::string str;
				REQUIRE(decompStrm.ReadBlock(str.data(), 10) == 10);
				CHECK(strncmp(str.c_str(), "AAAAAAAAAA", 10) == 0);
			}
		}

		WHEN("Write data block, then write data by bytes and then write block again")
		{
			compStrm.WriteBlock("AAA", 3);
			compStrm.WriteByte('A');
			compStrm.WriteByte('A');
			compStrm.WriteBlock("AAA", 3);
			compStrm.Flush();

			THEN("Bytes was compressed")
			{
				IInputPtr inStrm = std::make_unique<CMemoryInputStream>(v);
				CDecompressiveInputStream decompStrm(std::move(inStrm));
				std::string str;
				REQUIRE(decompStrm.ReadBlock(str.data(), 8) == 8);
				CHECK(strncmp(str.c_str(), "AAAAAAAA", 8) == 0);
			}
		}
	}
}