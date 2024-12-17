#include "../model/Ellipse.h"
#include "../model/Rectangle.h"
#include "../model/Shapes.h"
#include "../model/Triangle.h"

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

		WHEN("add handler on shape adding")
		{
			shapes.AddShape(std::make_unique<Rectangle>("rect", Frame{ { 10, 20 }, { 30, 40 } }));
			shapes.AddShape(std::make_unique<Ellipse>("ellipse", Frame{ { 10, 20 }, { 30, 40 } }));

			IShape* shape = nullptr;
			size_t pos = 0;
			auto connection = shapes.DoOnAddShape([&](IShape* s, const size_t p) {
				shape = s;
				pos = p;
			});

			AND_WHEN("add shape")
			{
				shapes.AddShape(std::make_unique<Triangle>("triangle", Frame{ { 10, 20 }, { 30, 40 } }));

				THEN("handler was called")
				{
					CHECK(shape == shapes.GetShape("triangle"));
					CHECK(pos == 2);
				}
			}
		}
	}
}