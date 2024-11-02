#include "../../external/core/CoutBufferFixture.h"
#include "../fileStorage/Path.h"
#include "../document/Document.h"
#include <catch.hpp>
#include <fstream>
class IDocument;

const Path STORAGE_DIR = "storage";
const Path EXPORT_DIR = "testSaveDocument";

SCENARIO_METHOD(CoutBufferFixture, "Document tests")
{
	GIVEN("Document")
	{
		create_directory(STORAGE_DIR);
		const std::shared_ptr<IDocument> document = std::make_shared<Document>(STORAGE_DIR);

		THEN("Can not undo and redo, has empty title")
		{
			CHECK_FALSE(document->CanUndo());
			CHECK_FALSE(document->CanRedo());
			CHECK(document->GetTitle().empty());
			CHECK(document->GetItemsCount() == 0);
		}

		WHEN("Add image")
		{
			document->InsertImage("cactus.png", 200, 300);

			THEN("There is an image at the first position")
			{
				CHECK_NOTHROW(document->GetItem(1));
				CHECK_THROWS(document->GetItem(2));
				CHECK(document->GetItemsCount() == 1);
				document->List();
				CHECK(GetOutput() == "Title: \n1. Image: 200 300 \"cactus.png\"\n");
			}
		}

		WHEN("Add paragraph")
		{
			document->InsertParagraph("Hello World");

			THEN("There is a paragraph at the first position")
			{
				CHECK(document->GetItemsCount() == 1);
				document->List();
				CHECK(GetOutput() == "Title: \n1. Paragraph: Hello World\n");
			}
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Delete documents items test")
{
	GIVEN("Document")
	{
		create_directory(STORAGE_DIR);
		const std::shared_ptr<IDocument> document = std::make_shared<Document>(STORAGE_DIR);

		WHEN("Insert image and paragraph")
		{
			CHECK_THROWS_AS(document->InsertParagraph("Hello", 2), std::out_of_range);
			document->InsertImage("cactus.png", 200, 300);
			document->InsertParagraph("Hello World", 1);

			THEN("Documents contains paragraph and image")
			{
				CHECK(document->GetItemsCount() == 2);
				document->List();
				CHECK(GetOutput() == "Title: \n"
					"1. Paragraph: Hello World\n"
					"2. Image: 200 300 \"cactus.png\"\n"
				);

				AND_THEN("can undo insertions")
				{
					document->Undo();
					document->Undo();

					THEN("document is empty")
					{
						CHECK(document->GetItemsCount() == 0);
					}
				}
			}

			AND_WHEN("Delete the second item")
			{
				CHECK_THROWS_AS(document->DeleteItem(3), std::out_of_range);
				document->DeleteItem(2);

				THEN("document contains only 1 item")
				{
					CHECK(document->GetItemsCount() == 1);
					document->List();
					CHECK(GetOutput() == "Title: \n"
						"1. Paragraph: Hello World\n"
					);
				}

				AND_WHEN("Delete one more item")
				{
					document->DeleteItem(1);

					THEN("Document is empty")
					{
						CHECK(document->GetItemsCount() == 0);
					}

					AND_WHEN("Can restore items")
					{
						REQUIRE(document->CanUndo());
						document->Undo();

						THEN("document contains only 1 item")
						{
							CHECK(document->GetItemsCount() == 1);
							document->List();
							CHECK(GetOutput() == "Title: \n"
								"1. Paragraph: Hello World\n"
							);
						}

						AND_WHEN("Can delete item again")
						{
							REQUIRE(document->CanRedo());
							document->Redo();


							THEN("Document is empty")
							{
								CHECK(document->GetItemsCount() == 0);
							}

							AND_WHEN("Restore both items")
							{
								document->Undo();
								document->Undo();

								THEN("Documents contains paragraph and image")
								{
									CHECK(document->GetItemsCount() == 2);
									document->List();
									CHECK(GetOutput() == "Title: \n"
										"1. Paragraph: Hello World\n"
										"2. Image: 200 300 \"cactus.png\"\n"
									);
								}

								WHEN("save document")
								{
									document->DeleteItem(2);
									document->Save(EXPORT_DIR);

									THEN("Document was saved")
									{
										CHECK(fs::exists(EXPORT_DIR));
										CHECK(fs::exists(EXPORT_DIR/"images"));
										CHECK(fs::exists(EXPORT_DIR/"index.html"));

										std::ifstream file(EXPORT_DIR/"index.html");
										std::stringstream fileContent;
										fileContent << file.rdbuf();
										CHECK(fileContent.str() ==
											"<html>\n"
											"<head>\n"
											"  <title></title>\n"
											"</head>\n"
											"<body>\n"
											"<p>Hello World</p>\n"
											"</body>\n"
											"</html>\n"
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
}