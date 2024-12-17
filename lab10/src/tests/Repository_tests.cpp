#include "../repository/Repository.h"

#include <catch.hpp>

SCENARIO("repository tests")
{
	GIVEN("An empty repository")
	{
		Repository<std::string> repository;

		THEN("repository is empty")
		{
			CHECK(repository.GetSize() == 0);
		}

		WHEN("add item to repository")
		{
			repository.Insert("1", "apple");

			THEN("item was added")
			{
				CHECK(repository.GetSize() == 1);
				CHECK(*repository.Find("1").value() == "apple");
			}
		}
	}
}
