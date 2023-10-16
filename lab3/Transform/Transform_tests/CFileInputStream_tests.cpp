#include "../../../external/catch2/catch.hpp"
#include "../Transform/CFileInputStream.h"

SCENARIO("CFileInputStream test")
{
	THEN("An exception is thrown when creating a stream from a non-existent file")
	{
		CHECK_THROWS_AS(CFileInputStream("non-existent-file.txt"), std::ios_base::failure);
	}

	GIVEN("File input stream from empty file")
	{
		std::ofstream file("test.txt", std::ofstream::out);
		file.close();
		CFileInputStream strm("test.txt");

		THEN("Eof has been reached")
		{
			CHECK(strm.IsEOF());
		}

		CHECK_THROWS_AS(strm.ReadByte(), std::ios_base::failure);
	}

	GIVEN("File input stream from file with one char")
	{
		std::ofstream file("test.txt", std::ofstream::out);
		file << 'A';
		file.close();
		CFileInputStream strm("test.txt");

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

	GIVEN("File input stream from file with manny chars")
	{
		std::ofstream file("test.txt", std::ofstream::out);
		file << "Hello, world!";
		file.close();
		CFileInputStream strm("test.txt");

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
			}
		}
	}
}