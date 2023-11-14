#include "../../../external/catch2/catch.hpp"
#include "../../../external/core/CoutBufferFixture.h"
#include "../HtmlEditor/CDocument.h"

SCENARIO_METHOD(CoutBufferFixture, "Document tests")
{
	GIVEN("Document")
	{
		CDocument document;

		THEN("Can not undo and redo, has empty title")
		{
			CHECK_FALSE(document.CanUndo());
			CHECK_FALSE(document.CanRedo());
			CHECK(document.GetTitle().empty());
			CHECK(document.GetItemsCount() == 0);
		}

		WHEN("Add image")
		{
			document.InsertImage("source/cactus.png", 200, 300);

			THEN("There is an image at the first position")
			{
				CHECK(document.GetItemsCount() == 1);
				document.List();
				CHECK(GetOutput() == "1. Image: 200 300 \"source/cactus.png\"\n");
			}
		}

		WHEN("Add paragraph")
		{
			document.InsertParagraph("Hello World");

			THEN("There is a paragraph at the first position")
			{
				CHECK(document.GetItemsCount() == 1);
				document.List();
				CHECK(GetOutput() == "1. Paragraph: Hello World\n");
			}
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Delete documents items test")
{
	GIVEN("Document")
	{
		CDocument document;

		WHEN("Insert image and paragraph")
		{
			CHECK_THROWS_AS(document.InsertParagraph("Hello", 2), std::out_of_range);
			document.InsertImage("source/cactus.png", 200, 300);
			document.InsertParagraph("Hello World", 1);

			THEN("Documents contains paragraph and image")
			{
				CHECK(document.GetItemsCount() == 2);
				document.List();
				CHECK(GetOutput() ==
					"1. Paragraph: Hello World\n"
					"2. Image: 200 300 \"source/cactus.png\"\n"
				);
			}

			AND_WHEN("Delete the second item")
			{
				CHECK_THROWS_AS(document.DeleteItem(3), std::out_of_range);
				document.DeleteItem(2);

				THEN("document contains only 1 item")
				{
					CHECK(document.GetItemsCount() == 1);
					document.List();
					CHECK(GetOutput() ==
						"1. Paragraph: Hello World\n"
					);
				}
				
				AND_WHEN("Delete one more item")
				{
					document.DeleteItem(1);

					THEN("Document is empty")
					{
						CHECK(document.GetItemsCount() == 0);
					}

					AND_WHEN("Can restore items")
					{
						REQUIRE(document.CanUndo());
						document.Undo();

						THEN("document contains only 1 item")
						{
							CHECK(document.GetItemsCount() == 1);
							document.List();
							CHECK(GetOutput() ==
								"1. Paragraph: Hello World\n"
							);
						}

						AND_WHEN("Can delete item again")
						{
							REQUIRE(document.CanRedo());
							document.Redo();


							THEN("Document is empty")
							{
								CHECK(document.GetItemsCount() == 0);
							}

							AND_WHEN("Restore both items")
							{
								document.Undo();
								document.Undo();

								THEN("Documents contains paragraph and image")
								{
									CHECK(document.GetItemsCount() == 2);
									document.List();
									CHECK(GetOutput() ==
										"1. Paragraph: Hello World\n"
										"2. Image: 200 300 \"source/cactus.png\"\n"
									);
								}
							}
						}
					}
				}
			}
		}
	}
}