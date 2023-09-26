#include "../../../external/catch2/catch.hpp"
#include "../Shapes/Shape.h"
#include "../Shapes/CircleBehavior.h"
#include "../Shapes/TriangleBehavior.h"
#include "../Shapes/TextBehavior.h"
#include "../Shapes/RectangleBehavior.h"
#include "../Shapes/LineBehavior.h"
#include "MockCanvasFixture.h"

SCENARIO_METHOD(MockCanvasFixture, "Shape tests")
{
	WHEN("Create some shape")
	{
		CircleBehavior circleDrawingStrategy(Point{ 5, 7 }, 3);
		Shape shape(std::make_unique<CircleBehavior>(circleDrawingStrategy), 0);

		THEN("Shape has black color")
		{
			CHECK(shape.GetColor() == 0);
		}

		AND_THEN("Shapes color can be changed")
		{
			shape.SetColor(15);
			CHECK(shape.GetColor() == 15);
		}
	}
}

SCENARIO_METHOD(MockCanvasFixture, "Triangle drawing")
{
	GIVEN("Shape with triangle drawing strategy")
	{
		TriangleBehavior triangleDrawingStrategy(Point{ 1, 1 }, Point{ 2, 2 }, Point{ 3, 3 });
		Shape shape(std::make_unique<TriangleBehavior>(triangleDrawingStrategy), 0);

		WHEN("Draw shape")
		{
			shape.Draw(mockCanvas.get());

			THEN("Three lines drawn at canvas")
			{
				CHECK(output.str() ==
					"Set color 0\n"
					"Move to (1, 1)\n"
					"Line to (2, 2)\n"
					"Line to (3, 3)\n"
					"Line to (1, 1)\n"
				);
			}
		}
	}
}

SCENARIO_METHOD(MockCanvasFixture, "Circle drawing")
{
	GIVEN("Shape with circle drawing strategy")
	{
		CircleBehavior circleDrawingStrategy(Point{ 5, 7 }, 3);
		Shape shape(std::make_unique<CircleBehavior>(circleDrawingStrategy), 0);

		WHEN("Draw shape")
		{
			shape.Draw(mockCanvas.get());

			THEN("Ellipse drawn at canvas")
			{
				CHECK(output.str() == "Set color 0\nDraw ellipse in (5, 7) with rx 3 and ry 3\n");
			}
		}
	}
}

SCENARIO_METHOD(MockCanvasFixture, "Line drawing")
{
	GIVEN("Shape with line drawing strategy")
	{
		LineBehavior lineDrawingStrategy(Point{ 1, 1 }, Point{ 2, 2 });
		Shape shape(std::make_unique<LineBehavior>(lineDrawingStrategy), 0);

		WHEN("Draw shape")
		{
			shape.Draw(mockCanvas.get());

			THEN("Three lines drawn at canvas")
			{
				CHECK(output.str() ==
					"Set color 0\n"
					"Move to (1, 1)\n"
					"Line to (2, 2)\n"
				);
			}
		}
	}
}

SCENARIO_METHOD(MockCanvasFixture, "Rectangle drawing")
{
	GIVEN("Shape with rectangle drawing strategy")
	{
		RectangleBehavior rectangleDrawingStrategy(Point{ 1, 1 }, 5, 3);
		Shape shape(std::make_unique<RectangleBehavior>(rectangleDrawingStrategy), 0);

		WHEN("Draw shape")
		{
			shape.Draw(mockCanvas.get());

			THEN("Four lines drawn at canvas")
			{
				CHECK(output.str() ==
					"Set color 0\n"
					"Move to (1, 1)\n"
					"Line to (6, 1)\n"
					"Line to (6, 4)\n"
					"Line to (1, 4)\n"
					"Line to (1, 1)\n"
				);
			}
		}
	}
}

SCENARIO_METHOD(MockCanvasFixture, "Text drawing")
{
	GIVEN("Text with rectangle drawing strategy")
	{
		TextBehavior textDrawingStrategy(Point{ 1, 1 }, 14, "Hello world!");
		Shape shape(std::make_unique<TextBehavior>(textDrawingStrategy), 0);

		WHEN("Draw shape")
		{
			shape.Draw(mockCanvas.get());

			THEN("Text drawn at canvas")
			{
				CHECK(output.str() == "Set color 0\nDraw text 'Hello world!' with font size 14 in (1, 1)\n");
			}
		}
	}
}

SCENARIO_METHOD(MockCanvasFixture, "Change Shapes drawing strategy")
{
	GIVEN("Shape with triangle drawing strategy")
	{
		TriangleBehavior triangleDrawingStrategy(Point{ 1, 1 }, Point{ 2, 2 }, Point{ 3, 3 });
		Shape shape(std::make_unique<TriangleBehavior>(triangleDrawingStrategy), 0);

		WHEN("Draw shape")
		{
			shape.Draw(mockCanvas.get());

			THEN("Three lines drawn at canvas")
			{
				CHECK(output.str() ==
					"Set color 0\n"
					"Move to (1, 1)\n"
					"Line to (2, 2)\n"
					"Line to (3, 3)\n"
					"Line to (1, 1)\n"
				);
			}

			AND_WHEN("Draw shape with another drawing strategy")
			{
				CircleBehavior circleDrawingStrategy(Point{ 5, 7 }, 3);
				shape.SetDrawingStrategy(std::make_unique<CircleBehavior>(circleDrawingStrategy));
				output = std::stringstream();
				shape.Draw(mockCanvas.get());

				THEN("Ellipse drawn at canvas")
				{
					CHECK(output.str() == "Set color 0\nDraw ellipse in (5, 7) with rx 3 and ry 3\n");
				}
			}
		}
	}
}
