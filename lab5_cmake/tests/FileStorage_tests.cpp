#include "../fileStorage/FileEntity.h"
#include "../fileStorage/FileStorage.h"
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
			FileEntity fileEntity(p, p);
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
			FileEntity fileEntity(p, p);
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

SCENARIO("file storage tests")
{
	WHEN("create directory for storage")
	{
		const Path storageDirPath = "./storage";
		create_directory(storageDirPath);

		THEN("storage directory exist")
		{
			FileStorage storage(storageDirPath);
			CHECK(fs::exists(storageDirPath));
		}

		CHECK_FALSE(fs::exists(storageDirPath));
	}

	GIVEN("file storage")
	{
		create_directory(STORAGE_PATH);

		WHEN("create storage")
		{
			FileStorage storage(STORAGE_PATH);

			AND_WHEN("add files")
			{
				auto file = storage.AddFile("cactus.png");

				THEN("added file exist")
				{
					CHECK(fs::exists(file->GetPath()));
				}
			}
		}
		CHECK_FALSE(fs::exists(STORAGE_PATH));
	}

	GIVEN("file storage")
	{
		create_directory(STORAGE_PATH);
		FileRefPtr file;

		WHEN("create storage")
		{
			FileStorage storage(STORAGE_PATH);

			AND_WHEN("add files")
			{
				file = storage.AddFile("cactus.png");

				THEN("added file exist")
				{
					CHECK(fs::exists(file->GetPath()));
				}
			}
		}

		CHECK(fs::exists(STORAGE_PATH));
		CHECK(fs::exists(file->GetPath()));
	}
}
