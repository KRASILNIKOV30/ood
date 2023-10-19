#include "../../../external/catch2/catch.hpp"
#include "../Transform/CMemoryInputStream.h"
#include <fstream>

SCENARIO("CMemoryInputStream test")
{
	GIVEN("Memory input stream from empty file")
	{
		CMemoryInputStream strm({});

		THEN("Eof has been reached")
		{
			CHECK(strm.IsEOF());
		}

		CHECK_THROWS_AS(strm.ReadByte(), std::ios_base::failure);
	}

	GIVEN("Memory input stream from file with one char")
	{
		CMemoryInputStream strm({'A'});

		THEN("Eof has not been reached")
		{
			CHECK_FALSE(strm.IsEOF());
		}

		WHEN("Read one byte")
		{
			CHECK(strm.ReadByte() == 'A');

			THEN("Eof has been reached")
			{
				CHECK(strm.IsEOF());
			}
		}
	}

	GIVEN("Memory input stream from file with many chars")
	{
		CMemoryInputStream strm({'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!'});

		THEN("Eof has not been reached")
		{
			CHECK_FALSE(strm.IsEOF());
		}

		WHEN("Read block less than current file data")
		{
			char* buffer = new char[7];
			auto readSize = strm.ReadBlock(buffer, 7);

			THEN("Block was fully read")
			{
				CHECK(readSize == 7);
				CHECK(strncmp(buffer, "Hello, ", 7) == 0);
				delete[] buffer;
			}
		}

		WHEN("Read block greater than current file data")
		{
			char* buffer = new char[14];
			auto readSize = strm.ReadBlock(buffer, 14);

			THEN("Block was not fully read")
			{
				CHECK(readSize == 13);
				CHECK(strncmp(buffer, "Hello, world!", 13) == 0);
				delete[] buffer;
			}
		}
	}
}