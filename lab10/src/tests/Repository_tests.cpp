#include "../repository/Repository.h"

#include <catch.hpp>
#include <utility>

class Item
{
public:
	Item(std::string id, std::string name)
		: m_id(std::move(id))
		, m_name(std::move(name))
	{
	}
	[[nodiscard]] std::string GetId() const
	{
		return m_id;
	}
	[[nodiscard]] std::string GetName() const
	{
		return m_name;
	}

private:
	std::string m_id;
	std::string m_name;
};

bool operator==(const Item& lhs, const std::string& rhs)
{
	return lhs.GetName() == rhs;
}

SCENARIO("repository tests")
{
	GIVEN("An empty repository")
	{
		Repository<Item> repository;

		THEN("repository is empty")
		{
			CHECK(repository.GetSize() == 0);
		}

		WHEN("add item to repository")
		{
			repository.Insert({ "1", "apple" });

			THEN("item was added")
			{
				CHECK(repository.GetSize() == 1);
				CHECK(*repository.Find("1").value() == "apple");
				repository.ForEach([&](const auto& str) {
					CHECK(*str == "apple");
					return true;
				});
			}

			AND_WHEN("remove this item")
			{
				repository.Remove("1");

				THEN("item was removed")
				{
					CHECK(repository.GetSize() == 0);
					CHECK_FALSE(repository.Find("1").has_value());
					int counter = 0;
					repository.ForEach([&](const auto&) {
						++counter;
						return true;
					});
					CHECK(counter == 0);
				}
			}

			AND_WHEN("add string with the same id")
			{
				repository.Insert({ "1", "banana" });

				THEN("item was not added")
				{
					CHECK(repository.GetSize() == 1);
					int counter = 0;
					repository.ForEach([&](const auto&) {
						++counter;
						return true;
					});
					CHECK(counter == 1);
				}
			}
		}

		WHEN("add 5 strings")
		{
			repository.Insert({ "1", "A" });
			repository.Insert({ "2", "B" });
			repository.Insert({ "3", "C" });
			repository.Insert({ "4", "D" });
			repository.Insert({ "5", "E" });

			THEN("5 strings was added")
			{
				CHECK(repository.GetSize() == 5);
				std::string result;
				repository.ForEach([&](const auto& str) {
					result += str->GetName();
					return true;
				});
				CHECK(result == "ABCDE");
			}

			AND_WHEN("Remove one string")
			{
				repository.Remove("3");

				THEN("item was removed")
				{
					CHECK(repository.GetSize() == 4);
					CHECK(*repository.Find("1").value() == "A");
					CHECK(*repository.Find("2").value() == "B");
					CHECK_FALSE(repository.Find("3").has_value());
					CHECK(*repository.Find("4").value() == "D");
					CHECK(*repository.Find("5").value() == "E");
					std::string result;
					repository.ForEach([&](const auto& item) {
						result += item->GetName();
						return true;
					});
					CHECK(result == "ABDE");
				}
			}

			AND_WHEN("Add another one string to begin")
			{
				repository.Insert({ "6", "F" }, 0);

				THEN("item was added")
				{
					CHECK(repository.GetSize() == 6);
					CHECK(*repository.Find("1").value() == "A");
					CHECK(*repository.Find("2").value() == "B");
					CHECK(*repository.Find("3").value() == "C");
					CHECK(*repository.Find("4").value() == "D");
					CHECK(*repository.Find("5").value() == "E");
					CHECK(*repository.Find("6").value() == "F");
					std::string result;
					repository.ForEach([&](const auto& item) {
						result += item->GetName();
						return true;
					});
					CHECK(result == "FABCDE");
				}
			}

			THEN("can get one of that items")
			{
				CHECK(*repository.Get("1") == "A");
				CHECK(*repository.Get(1) == "B");
				CHECK_THROWS(repository.Get("6"));
				CHECK_THROWS(repository.Get(5));
			}
		}
	}
}
