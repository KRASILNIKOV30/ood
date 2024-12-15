#define CATCH_CONFIG_MAIN
#include "../model/Ellipse.h"
#include "../model/Rectangle.h"
#include "../model/Triangle.h"

#include <catch.hpp>

SCENARIO("Rectangle tests")
{
	GIVEN("rectangle")
	{
		const Rectangle rectangle("rectId", { { 10, 20 }, { 30, 40 } });

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