#include "../documentItems/Image.h"
#include "../documentItems/Paragraph.h"
#include "../fileStorage/FileStorage.h"
#include "../history/UndoManager.h"

#include <catch.hpp>

SCENARIO("resize image")
{
	GIVEN("An image")
	{
		UndoManager history;
		FileStorage storage("./storage");
		auto file = storage.AddFile("cactus.png");
		auto image = std::make_shared<Image>(100, 100, file, [&](auto const& edit) {
			history.AddEdit(edit);
		});

		WHEN("resize image")
		{
			image->Resize(200, 200);

			THEN("image has resized")
			{
				CHECK(image->GetWidth() == 200);
				CHECK(image->GetHeight() == 200);
			}

			WHEN("undo resized")
			{
				history.Undo();

				THEN("image has unresized")
				{
					CHECK(image->GetWidth() == 100);
					CHECK(image->GetHeight() == 100);
				}

				WHEN("redo resize")
				{
					history.Redo();

					THEN("image has resized")
					{
						CHECK(image->GetWidth() == 200);
						CHECK(image->GetHeight() == 200);
					}

					WHEN("resize image again")
					{
						image->Resize(300, 300);

						THEN("edits has pasted together")
						{
							CHECK(history.GetEditCount() == 1);
							CHECK(image->GetWidth() == 300);
							CHECK(image->GetHeight() == 300);
						}

						WHEN("undo resize")
						{
							history.Undo();

							THEN("both resizes was undone")
							{
								CHECK(image->GetWidth() == 100);
								CHECK(image->GetHeight() == 100);
							}

							WHEN("redo image resize")
							{
								history.Redo();

								THEN("image has resized")
								{
									CHECK(image->GetWidth() == 300);
									CHECK(image->GetHeight() == 300);
								}
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO("replace text")
{
	GIVEN("An text")
	{
		UndoManager history;
		auto paragraph = std::make_shared<Paragraph>("hello", [&](auto const& edit) {
			history.AddEdit(edit);
		});

		WHEN("replace text")
		{
			paragraph->SetText("hello world");

			THEN("text has resized")
			{
				CHECK(paragraph->GetText() == "hello world");
			}

			WHEN("undo replace")
			{
				history.Undo();

				THEN("text has replaced back")
				{
					CHECK(paragraph->GetText() == "hello");
				}

				WHEN("redo resize")
				{
					history.Redo();

					THEN("text has resized")
					{
						CHECK(paragraph->GetText() == "hello world");
					}

					WHEN("replace text again")
					{
						paragraph->SetText("hello new world");

						THEN("edits has pasted together")
						{
							CHECK(history.GetEditCount() == 1);
							CHECK(paragraph->GetText() == "hello new world");
						}

						WHEN("undo resize")
						{
							history.Undo();

							THEN("both replaces was undone")
							{
								CHECK(paragraph->GetText() == "hello");
							}

							WHEN("redo text resize")
							{
								history.Redo();

								THEN("text has resized")
								{
									// CHECK(paragraph->GetText() == "hello new world");
								}
							}
						}
					}
				}
			}
		}
	}
}
