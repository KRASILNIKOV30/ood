#define CATCH_CONFIG_MAIN
#include "../model/Ellipse.h"
#include "../model/Rectangle.h"
#include "../model/Triangle.h"

#include <catch.hpp>

SCENARIO("Rectangle tests")
{
	GIVEN("rectangle")
	{
		Rectangle rectangle("rectId", { { 10, 20 }, { 30, 40 } });

		THEN("can get frame")
		{
			CHECK(rectangle.GetFrame() == Frame{ { 10, 20 }, { 30, 40 } });
		}

		AND_THEN("can get type")
		{
			CHECK(rectangle.GetType() == "rectangle");
		}

		AND_THEN("can get id")
		{
			CHECK(rectangle.GetId() == "rectId");
		}

		WHEN("move")
		{
			constexpr Frame frame{ { 100, 20 }, { 30, 40 } };
			rectangle.Reframe(frame);

			THEN("shape moved")
			{
				CHECK(rectangle.GetFrame() == frame);
			}
		}

		WHEN("resize")
		{
			constexpr Frame frame{ { 10, 20 }, { 300, 400 } };
			rectangle.Reframe(frame);

			THEN("shape resized")
			{
				CHECK(rectangle.GetFrame() == frame);
			}
		}

		WHEN("subscribe on reframe")
		{
			int counter = 0;
			Frame subscribedFrame{ { 10, 20 }, { 30, 40 } };
			const auto connection = rectangle.DoOnReframe([&](const auto& frame) {
				subscribedFrame = frame;
				counter++;
			});

			WHEN("reframe")
			{
				Frame newFrame{ { 100, 200 }, { 300, 400 } };
				rectangle.Reframe(newFrame);

				THEN("frame changed")
				{
					rectangle.Reframe(newFrame);
					CHECK(subscribedFrame == newFrame);
					CHECK(counter == 1);
				}
			}

			WHEN("reframe with the same frame")
			{
				Frame newFrame{ { 10, 20 }, { 30, 40 } };
				rectangle.Reframe(newFrame);

				THEN("frame changed")
				{
					rectangle.Reframe(newFrame);
					CHECK(counter == 0);
				}
			}
		}
	}
}

SCENARIO("Triangle tests")
{
	GIVEN("triangle")
	{
		const Triangle triangle("triangleId", { { 10, 20 }, { 30, 40 } });

		THEN("can get frame")
		{
			CHECK(triangle.GetFrame() == Frame{ { 10, 20 }, { 30, 40 } });
		}

		AND_THEN("can get type")
		{
			CHECK(triangle.GetType() == "triangle");
		}

		AND_THEN("can get id")
		{
			CHECK(triangle.GetId() == "triangleId");
		}
	}
}

SCENARIO("Ellipse tests")
{
	GIVEN("ellipse")
	{
		const Ellipse ellipse("ellipseId", { { 10, 20 }, { 30, 40 } });

		THEN("can get frame")
		{
			CHECK(ellipse.GetFrame() == Frame{ { 10, 20 }, { 30, 40 } });
		}

		AND_THEN("can get type")
		{
			CHECK(ellipse.GetType() == "ellipse");
		}

		AND_THEN("can get id")
		{
			CHECK(ellipse.GetId() == "ellipseId");
		}
	}
}