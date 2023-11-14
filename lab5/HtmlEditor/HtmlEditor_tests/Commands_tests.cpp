#include "../../../external/catch2/catch.hpp"
#include "../HtmlEditor/CCommands.h"
#include "../HtmlEditor/CImage.h"
#include "../HtmlEditor/CParagraph.h"

SCENARIO("Resize image command test")
{
	GIVEN("Resize image commmand")
	{
		auto const image = std::make_shared<CImage>(100, 100, "./source/cactus.png");
		ResizeImageCommand command(image, 200, 300);

		WHEN("Execute command")
		{
			command.Execute();

			THEN("Images size has changed")
			{
				CHECK(image->GetWidth() == 200);
				CHECK(image->GetHeight() == 300);
			}

			AND_WHEN("Unexecute command")
			{
				command.Unexecute();

				THEN("Images size has changed to the first value")
				{
					CHECK(image->GetWidth() == 100);
					CHECK(image->GetHeight() == 100);
				}
			}
		}
	}
}

SCENARIO("Replace text command test")
{
	GIVEN("Replace text commmand")
	{
		auto const paragraph = std::make_shared<CParagraph>("Hello");
		ReplaceTextCommand command(paragraph, "World");

		WHEN("Execute command")
		{
			command.Execute();

			THEN("Paragraph text has changed")
			{
				CHECK(paragraph->GetText() == "World");
			}

			AND_WHEN("Unexecute command")
			{
				command.Unexecute();

				THEN("Paragrapg text has changed to the first value")
				{
					CHECK(paragraph->GetText() == "Hello");
				}
			}
		}
	}
}