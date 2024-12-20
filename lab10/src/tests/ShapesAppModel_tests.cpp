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
					shapes.ForEach([&](const IShapeAppModel*) {
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
					shapes.ForEach([&](const IShapeAppModel*) {
						counter++;
						return true;
					});
					CHECK(counter == 1);
				}
			}
		}
	}
}