#include "../../../external/catch2/catch.hpp"
#include "../HtmlEditor/CCommands.h"
#include "../HtmlEditor/CImage.h"
#include "../HtmlEditor/History.h"

SCENARIO("History tests")
{
	GIVEN("History")
	{
		History history;

		THEN("Can not undo and redo")
		{
			CHECK_FALSE(history.CanUndo());
			CHECK_FALSE(history.CanRedo());
		}

		WHEN("Add and execute command")
		{
			auto const image = std::make_shared<CImage>(100, 100, "./source/cactus.png");
			history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(image, 200, 300));

			THEN("Image has resized")
			{
				CHECK(image->GetWidth() == 200);
				CHECK(image->GetHeight() == 300);
			}

			AND_WHEN("Undo action")
			{
				CHECK(history.CanUndo());
				CHECK_FALSE(history.CanRedo());
				history.Undo();

				THEN("Image has resized")
				{
					CHECK(image->GetWidth() == 100);
					CHECK(image->GetHeight() == 100);
				}

				AND_THEN("Can redo")
				{
					CHECK(history.CanRedo());
					history.Redo();
					CHECK(image->GetWidth() == 200);
					CHECK(image->GetHeight() == 300);
				}
			}
		}
	}
}

SCENARIO("History size test")
{
	GIVEN("History with 10 commands")
	{
		History history;
		auto const image = std::make_shared<CImage>(100, 100, "./source/cactus.png");
		for (int i = 1; i <= 10; ++i)
		{
			history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(image, i, i));
		}

		WHEN("Add the 11th command")
		{
			history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(image, 11, 11));

			THEN("The first command has deleted from history")
			{
				int executedCommandsCount = 0;
				while (history.CanUndo())
				{
					history.Undo();
					++executedCommandsCount;
				}
				CHECK(executedCommandsCount == 10);
				CHECK(image->GetWidth() == 1);
				CHECK(image->GetHeight() == 1);
			}
		}
	}
}