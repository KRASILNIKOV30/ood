#include "../fileStorage/FileEntity.h"
#include <fstream>
#include <catch.hpp>

const Path STORAGE_PATH = "./storage";

SCENARIO("file entity tests")
{
	GIVEN("file entity without keep alive")
	{
		const Path p = "test.txt";
		std::ofstream file{ p };
		{
			FileEntity fileEntity(p);
			CHECK(fileEntity.GetPath() == p);
			CHECK(fs::exists(p));
		}
		CHECK_FALSE(fs::exists(p));
	}

	GIVEN("file entity with keep alive")
	{
		const Path p = "test.txt";
		std::ofstream file{ p };
		{
			FileEntity fileEntity(p);
			CHECK(fs::exists(p));
			fileEntity.KeepAlive();
		}
		CHECK(fs::exists(p));
		fs::remove(p);
	}
}
