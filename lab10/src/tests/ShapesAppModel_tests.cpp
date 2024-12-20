#include "../appModel/ShapesAppModel.h"
#include "../model/Shapes.h"

#include <catch.hpp>

SCENARIO("shapes app model tests")
{
	GIVEN("An empty app model")
	{
		std::unique_ptr<IShapes> shapesDomain = std::make_unique<Shapes>();
		ShapesAppModel shapes(shapesDomain.get());

		WHEN("add shape")
		{
			shapes.AddShape("rectangle");

			THEN("can get this shape")
			{
				auto const shape = shapes.GetShape(0);
				CHECK(shape->GetType() == "rectangle");
				CHECK(shape->GetFrame() == DEFAULT_FRAME);
			}

			THEN("can get this shape from constant model")
			{
				auto const shape = const_cast<const ShapesAppModel*>(&shapes)->GetShape(0);
				CHECK(shape->GetType() == "rectangle");
				CHECK(shape->GetFrame() == DEFAULT_FRAME);
			}

			AND_WHEN("get shape with non-existent id")
			{
				CHECK_THROWS(shapes.GetShape("non-existent id"));
			}

			AND_WHEN("remove shape")
			{
				shapes.RemoveShape("0");

				THEN("shape is removed")
				{
					CHECK_THROWS(shapes.GetShape("0"));
					int counter = 0;
					shapes.ForEach([&](const auto&) {
						counter++;
						return true;
					});
					CHECK(counter == 0);
				}
			}

			AND_WHEN("remove shape with non-existent id")
			{
				CHECK_THROWS(shapes.RemoveShape("non-existent-id"));

				THEN("shape is not removed")
				{
					CHECK_FALSE(shapes.GetShape("0") == nullptr);
					int counter = 0;
					shapes.ForEach([&](const auto&) {
						counter++;
						return true;
					});
					CHECK(counter == 1);
				}
			}
		}

		WHEN("add handler on shape adding")
		{
			shapes.AddShape("rectangle");
			shapes.AddShape("ellipse");

			IShapeAppModelPtr shape;
			size_t pos = 0;
			auto connection = shapes.DoOnAddShape([&](auto const& s, auto p) {
				shape = s;
				pos = p;
			});

			AND_WHEN("add shape")
			{
				shapes.AddShape("triangle");

				THEN("handler was called")
				{
					CHECK(shape == shapes.GetShape(2));
					CHECK(pos == 2);
				}
			}
		}

		WHEN("add handler on shape removing")
		{
			shapes.AddShape("rectangle");
			shapes.AddShape("ellipse");
			shapes.AddShape("triangle");

			std::string id;
			auto connection = shapes.DoOnRemoveShape([&](auto const& removedId) {
				id = removedId;
			});

			AND_WHEN("remove shape")
			{
				shapes.RemoveShape("1");

				THEN("handler was called")
				{
					CHECK(id == "1");
				}
			}
		}

		WHEN("add 2 shapes")
		{
			shapes.AddShape("rectangle");
			shapes.AddShape("ellipse");

			AND_WHEN("undo")
			{
				CHECK(shapes.CanUndo());
				shapes.Undo();

				THEN("last shape was deleted")
				{
					CHECK_FALSE(shapes.GetShape(0) == nullptr);
					CHECK_THROWS(shapes.GetShape(1));
					CHECK(shapes.GetSize() == 1);

					AND_WHEN("redo")
					{
						CHECK(shapes.CanRedo());
						shapes.Redo();

						THEN("last shape was added")
						{
							CHECK(shapes.GetShape(0)->GetType() == "rectangle");
							CHECK(shapes.GetShape(1)->GetType() == "ellipse");
							CHECK(shapes.GetSize() == 2);
						}
					}
				}
			}

			AND_WHEN("undo twice")
			{
				shapes.Undo();
				shapes.Undo();

				THEN("can not undo again")
				{
					CHECK_FALSE(shapes.CanUndo());
				}

				THEN("all shapes deleted")
				{
					CHECK(shapes.GetSize() == 0);
				}

				AND_WHEN("redo twice")
				{
					shapes.Redo();
					shapes.Redo();

					THEN("can not redo again")
					{
						CHECK_FALSE(shapes.CanRedo());
					}

					THEN("all shapes added")
					{
						CHECK(shapes.GetShape(0)->GetType() == "rectangle");
						CHECK(shapes.GetShape(1)->GetType() == "ellipse");
						CHECK(shapes.GetSize() == 2);
					}
				}
			}

			AND_WHEN("remove shape")
			{
				shapes.RemoveShape("0");
				CHECK(shapes.GetShape(0)->GetType() == "ellipse");

				AND_WHEN("undo")
				{
					CHECK(shapes.CanUndo());
					shapes.Undo();

					THEN("shape added")
					{
						CHECK(shapes.GetShape(0)->GetType() == "rectangle");
						CHECK(shapes.GetShape(1)->GetType() == "ellipse");
						CHECK(shapes.GetSize() == 2);
					}

					AND_WHEN("redo")
					{
						CHECK(shapes.CanRedo());
						shapes.Redo();

						THEN("shape removed")
						{
							CHECK(shapes.GetSize() == 1);
							CHECK(shapes.GetShape(0)->GetType() == "ellipse");
							CHECK_THROWS(shapes.GetShape(1)->GetType());
						}
					}
				}
			}

			AND_WHEN("remove shape twice")
			{
				shapes.RemoveShape("0");
				shapes.RemoveShape("1");
				CHECK(shapes.GetSize() == 0);

				AND_WHEN("undo twice")
				{
					shapes.Undo();
					shapes.Undo();

					THEN("shapes added")
					{
						CHECK(shapes.GetShape(0)->GetType() == "rectangle");
						CHECK(shapes.GetShape(1)->GetType() == "ellipse");
						CHECK(shapes.GetSize() == 2);
					}

					AND_WHEN("redo twice")
					{
						CHECK(shapes.CanRedo());
						shapes.Redo();
						shapes.Redo();

						THEN("shapes removed")
						{
							CHECK(shapes.GetSize() == 0);
						}
					}
				}
			}
		}
	}
}