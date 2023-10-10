#include <iostream>
#include <sstream>
#include "../../../external/catch2/catch.hpp"
#include "../Factory/CEllipse.h"
#include "../Factory/CShape.h"
#include "../Factory/CRectangle.h"
#include "../Factory/CRegularPolygon.h"
#include "../Factory/CTriangle.h"
#include "../Factory/MockCanvas.h"
#include "../Factory/Point.h"


struct CoutBufferFixture
{
	std::stringstream buffer;
	std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

	std::string GetOutput() const
	{
		return buffer.str();
	}

	void ClearOutput()
	{
		buffer.str(std::string());
	}

	~CoutBufferFixture()
	{
		std::cout.rdbuf(old);
	}
};

SCENARIO_METHOD(CoutBufferFixture, "Drawing figures")
{
	GIVEN("Mock canvas")
	{
		MockCanvas canvas;

		WHEN("Drawing rectangle")
		{
			CRectangle rect(Point{ 3, 3 }, 10, 8, Color::Green);
			rect.Draw(canvas);

			THEN("Canvas draw rectangle")
			{
				CHECK(GetOutput() ==
					"Set color green\n"
					"Draw line from (3, 3) to (13, 3)\n"
					"Draw line from (13, 3) to (13, 11)\n"
					"Draw line from (13, 11) to (3, 11)\n"
					"Draw line from (3, 11) to (3, 3)\n"
				);
			}
		}

		WHEN("Drawing triangle")
		{
			CTriangle triangle(Point{ 1, 1 }, Point{ 2, 2 }, Point{ 3, 3 }, Color::Yellow);
			triangle.Draw(canvas);

			THEN("Canvas draw triangle")
			{
				CHECK(GetOutput() ==
					"Set color yellow\n"
					"Draw line from (1, 1) to (2, 2)\n"
					"Draw line from (2, 2) to (3, 3)\n"
					"Draw line from (3, 3) to (1, 1)\n"
				);
			}
		}

		WHEN("Drawing ellipse")
		{
			CEllipse ellipse(Point{ 1, 1 }, 5, 3, Color::Pink);
			ellipse.Draw(canvas);

			THEN("Canvas draw ellipse")
			{
				CHECK(GetOutput() ==
					"Set color pink\n"
					"Draw ellipse from (1, 1) with width 5 and height 3\n"
				);
			}
		}

		WHEN("Drawing regular polygon")
		{
			CRegularPolygon polygon(Point{ 5, 5 }, 5, 4, Color::Blue);
			polygon.Draw(canvas);

			THEN("Canvas draw regular polygon")
			{
				CHECK(GetOutput() ==
					"Set color blue\n"
					"Draw line from (10, 5) to (5, 10)\n"
					"Draw line from (5, 10) to (0, 5)\n"
					"Draw line from (0, 5) to (5, 0)\n"
					"Draw line from (5, 0) to (10, 5)\n"
				);
			}
		}
	}
}