#include "../../../external/catch2/catch.hpp"
#include "../HtmlEditor/CParagraph.h"

SCENARIO("Paragraph tests")
{
	GIVEN("Paragraph")
	{
		CParagraph paragraph("Hello");

		THEN("Can get paragraph text")
		{
			CHECK(paragraph.GetText() == "Hello");
		}

		WHEN("Change text")
		{
			paragraph.SetText("World");

			THEN("Paragraphs text has changed")
			{
				CHECK(paragraph.GetText() == "World");
			}
		}
	}
}