#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../menu/Menu.h"

SCENARIO("add items to menu and run it")
{
	GIVEN("Menu")
	{
		std::stringstream input;
		std::stringstream output;
		Menu menu(input, output);
		int counter = 0;

		WHEN("add commands to menu")
		{
			menu.AddItem(
				"increment",
				"increment counter",
				[&counter](std::istream&) { ++counter; });

			menu.AddItem(
				"add",
				"add some parameters to counter",
				[&counter](std::istream& strm) {
					int i;
					while (strm >> i)
					{
						counter += i;
					}
				});

			menu.AddItem(
				"exit",
				"exit menu",
				[&](std::istream&) { menu.Exit(); });

			THEN("can run menu")
			{
				input << "increment" << std::endl;
				input << "add 2 2" << std::endl;
				input << "exit" << std::endl;
				menu.Run();

				std::stringstream expected;
				expected << "Commands list:" << std::endl;
				expected << "  increment: increment counter" << std::endl;
				expected << "  add: add some parameters to counter" << std::endl;
				expected << "  exit: exit menu" << std::endl;
				expected << ">>>";

				CHECK(expected.str() == output.str());
				CHECK(counter == 5);
			}
		}
	}
}
