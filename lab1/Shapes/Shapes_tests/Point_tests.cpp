#include "../../../external/catch2/catch.hpp"
#include "../Shapes/Point.h"
#include "../Shapes/Common.h"
#include <sstream>

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

		AND_THEN("Adding point")
		{
			CHECK(point + Point{ 1, 1.5 } == Point{ 4, 7 });
			point += Point{ 1, 1.5 };
			CHECK(point == Point{ 4, 7 });
		}

		AND_THEN("Substraction point")
		{
			CHECK(point - Point{ 1, 1.5 } == Point{ 2, 4 });
		}

		AND_THEN("Point can be outputed")
		{
			std::stringstream output;
			output << point;
			CHECK(output.str() == "(3, 5.5)");
		}
	}
}