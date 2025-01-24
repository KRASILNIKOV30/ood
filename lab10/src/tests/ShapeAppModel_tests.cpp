#include "../appModel/IShapeAppModel.h"
#include "../appModel/ShapeAppModel.h"
#include "../history/UndoManager.h"
#include "../model/Rectangle.h"

#include <catch.hpp>
SCENARIO("shape app model tests")
{
	GIVEN("a shape from a domain shape")
	{
		UndoManager history;
		Frame frame{ { 10, 20 }, { 30, 40 } };
		const IShapePtr domainShape = std::make_shared<Rectangle>("rectId", frame);
		const IShapeAppModelPtr shape = std::make_shared<ShapeAppModel>(domainShape, [&](auto edit) {
			history.AddEdit(edit);
		});

		THEN("can get frame")
		{
			CHECK(shape->GetFrame() == Frame{ { 10, 20 }, { 30, 40 } });
		}

		AND_THEN("can get type")
		{
			CHECK(shape->GetType() == "rectangle");
		}

		AND_THEN("can get id")
		{
			CHECK(shape->GetId() == "rectId");
		}

		WHEN("reframe shape")
		{
			Frame newFrame{ { 50, 30 }, { 200, 200 } };
			shape->Reframe(newFrame);

			THEN("shape has reframed")
			{
				CHECK(shape->GetFrame() == newFrame);
			}

			WHEN("undo reframed")
			{
				history.Undo();

				THEN("shape has unreframed")
				{
					CHECK(shape->GetFrame() == frame);
				}

				WHEN("redo reframe")
				{
					history.Redo();

					THEN("shape has reframed")
					{
						CHECK(shape->GetFrame() == newFrame);
					}
				}
			}

			WHEN("reframe shape again")
			{
				Frame bigFrame{ { 100, 200 }, { 300, 400 } };
				shape->Reframe(bigFrame);

				THEN("edits has pasted together")
				{
					CHECK(history.GetEditCount() == 1);
					CHECK(shape->GetFrame() == bigFrame);
				}

				WHEN("undo reframe")
				{
					history.Undo();

					THEN("both reframes was undone")
					{
						CHECK(shape->GetFrame() == frame);
					}

					WHEN("redo shape reframe")
					{
						history.Redo();

						THEN("shape has reframed")
						{
							CHECK(shape->GetFrame() == bigFrame);
						}
					}
				}
			}
		}
	}
}
