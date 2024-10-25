#include "../fileStorage/FileEntity.h"
#include "../fileStorage/FolderEntity.h"

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
		std::ofstream{ p };
		{
			FileEntity fileEntity(p);
			CHECK(fs::exists(p));
			fileEntity.KeepAlive();
		}
		CHECK(fs::exists(p));
		fs::remove(p);
	}
}

SCENARIO("folder entity tests")
{
	GIVEN("folder")
	{
		const Path p = "testFolder";
		create_directory(p);

		WHEN("folder is empty")
		{
			{
				FolderEntity folderEntity(p);
			}

			THEN("folder has been removed")
			{
				CHECK_FALSE(fs::exists(p));
			}
		}

		WHEN("folder is not empty")
		{
			std::ofstream file{ p / "test.txt" };
			{
				FolderEntity folderEntity(p);
			}

			THEN("folder has not been removed")
			{
				CHECK(fs::exists(p));
			}

			fs::remove(p / "test.txt");
			fs::remove(p);
		}
	}
}
