#include "../model/Rectangle.h"
#include "../model/Shapes.h"
#include <catch.hpp>

SCENARIO("shapes tests")
{
	GIVEN("an empty shapes model")
	{
		Shapes shapes;

		WHEN("add shape")
		{
			shapes.AddShape(std::make_unique<Rectangle>("rect", Frame{ { 10, 20 }, { 30, 40 } }));

			THEN("can get this shape")
			{
				auto const shape = shapes.GetShape("rect");
				CHECK(shape->GetType() == "rectangle");
				CHECK(shape->GetFrame() == Frame{ { 10, 20 }, { 30, 40 } });
				CHECK(shape->GetId() == "rect");
			}

			AND_WHEN("find shape with non-existent id")
			{
				auto const shape = shapes.GetShape("non-existent id");

				THEN("shape not found")
				{
					CHECK(shape == nullptr);
				}
			}

			AND_WHEN("add shape with the same id")
			{
				shapes.AddShape(std::make_unique<Rectangle>("rect", Frame{ { 10, 20 }, { 30, 40 } }));

				THEN("shape is not added")
				{
					int counter = 0;
					shapes.ForEach([&](const IShape*) {
						counter++;
						return true;
					});
					CHECK(counter == 1);
				}
			}

			AND_WHEN("remove shape")
			{
				shapes.RemoveShape("rect");

				THEN("shape is removed")
				{
					CHECK(shapes.GetShape("rect") == nullptr);
					int counter = 0;
					shapes.ForEach([&](const IShape*) {
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
					CHECK_FALSE(shapes.GetShape("rect") == nullptr);
					int counter = 0;
					shapes.ForEach([&](const IShape*) {
						counter++;
						return true;
					});
					CHECK(counter == 1);
				}
			}
		}
	}
}