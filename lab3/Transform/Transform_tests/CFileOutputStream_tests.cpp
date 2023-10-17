#include "../../../external/catch2/catch.hpp"
#include "../Transform/CFileOutputStream.h"

SCENARIO("File output stream test")
{
	GIVEN("File output stream")
	{
		CFileOutputStream strm("out.txt");

		WHEN("Write one byte to file")
		{
			strm.WriteByte('A');
			strm.Close();

			THEN("Byte has been written")
			{
				std::ifstream ifstrm("out.txt");
				CHECK(ifstrm.get() == 'A');
				ifstrm.close();
			}
		}

		//Протестировать на больших данных (exe)
		AND_WHEN("Write full data block to file")
		{
			char* const src = new char[14]{"Hello, world!"};
			strm.WriteBlock(src, 14);
			strm.Close();

			THEN("Block has been fully written")
			{
				std::ifstream ifstrm("out.txt");
				std::string str;
				std::getline(ifstrm, str);
				CHECK(strcmp(str.c_str(), "Hello, world!") == 0);
				ifstrm.close();
			}
		}

		AND_WHEN("Write not full data block to file")
		{
			char* const src = new char[14]{"Hello, world!"};
			strm.WriteBlock(src, 5);
			strm.Close();

			THEN("Block has been fully written")
			{
				std::ifstream ifstrm("out.txt");
				std::string str;
				std::getline(ifstrm, str);
				CHECK(strcmp(str.c_str(), "Hello") == 0);
				ifstrm.close();
			}
		}
	}
}