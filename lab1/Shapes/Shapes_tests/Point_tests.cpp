#include "../../../external/catch2/catch.hpp"
#include "../Shapes/Point.h"
#include "../Shapes/Common.h"

SCENARIO("Point test")
{
	WHEN("Create point")
	{
		Point point{ 3, 5.5 };

		THEN("Point has coordinates")
		{
			CHECK(IsEquals(point.x, 3));
			CHECK(IsEquals(point.y, 5.5));
			CHECK(point == Point{ 3.0, 5.5 });
		}

		AND_WHEN("Adding point")
		{
			CHECK(point + Point{ 1, 1.5 } == Point{ 4, 7 });
			point += Point{ 1, 1.5 };
			CHECK(point == Point{ 4, 7 });

		}
	}
}