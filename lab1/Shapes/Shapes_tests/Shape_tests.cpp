#include "../../../external/catch2/catch.hpp"
#include "../Shapes/Common.h"
#include "../Shapes/Shape.h"
#include "../Shapes/CircleDrawingStrategy.h"
#include "../Shapes/TriangleDrawingStrategy.h"
#include "../Shapes/TextDrawingStrategy.h"
#include "../Shapes/RectangleDrawingStrategy.h"
#include "../Shapes/LineDrawingStrategy.h"

struct MockCanvasFixture
{
	fakeit::Mock<ICanvas> mockCanvas;
	std::stringstream output = std::stringstream();

	MockCanvasFixture()
	{
		DefineMockCanvasBehavior(mockCanvas, output);
	}
};

SCENARIO_METHOD(MockCanvasFixture, "Shape tests")
{
	WHEN("Create some shape")
	{
		CircleDrawingStrategy circleDrawingStrategy(Point{ 5, 7 }, 3);
		Shape shape(std::make_unique<CircleDrawingStrategy>(circleDrawingStrategy));

		THEN("Shape has default black color")
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
		TriangleDrawingStrategy triangleDrawingStrategy(Point{ 1, 1 }, Point{ 2, 2 }, Point{ 3, 3 });
		Shape shape(std::make_unique<TriangleDrawingStrategy>(triangleDrawingStrategy));

		WHEN("Draw shape")
		{
			shape.Draw(mockCanvas.get());

			THEN("Three lines drawn at canvas")
			{
				CHECK(output.str() ==
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
		CircleDrawingStrategy circleDrawingStrategy(Point{ 5, 7 }, 3);
		Shape shape(std::make_unique<CircleDrawingStrategy>(circleDrawingStrategy));

		WHEN("Draw shape")
		{
			shape.Draw(mockCanvas.get());

			THEN("Ellipse drawn at canvas")
			{
				CHECK(output.str() == "Draw ellipse in (5, 7) with rx 3 and ry 3\n");
			}
		}
	}
}

SCENARIO_METHOD(MockCanvasFixture, "Line drawing")
{
	GIVEN("Shape with line drawing strategy")
	{
		LineDrawingStrategy lineDrawingStrategy(Point{ 1, 1 }, Point{ 2, 2 });
		Shape shape(std::make_unique<LineDrawingStrategy>(lineDrawingStrategy));

		WHEN("Draw shape")
		{
			shape.Draw(mockCanvas.get());

			THEN("Three lines drawn at canvas")
			{
				CHECK(output.str() ==
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
		RectangleDrawingStrategy rectangleDrawingStrategy(Point{ 1, 1 }, 5, 3);
		Shape shape(std::make_unique<RectangleDrawingStrategy>(rectangleDrawingStrategy));

		WHEN("Draw shape")
		{
			shape.Draw(mockCanvas.get());

			THEN("Four lines drawn at canvas")
			{
				CHECK(output.str() ==
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
		TextDrawingStrategy textDrawingStrategy(Point{ 1, 1 }, 14, "Hello world!");
		Shape shape(std::make_unique<TextDrawingStrategy>(textDrawingStrategy));

		WHEN("Draw shape")
		{
			shape.Draw(mockCanvas.get());

			THEN("Text drawn at canvas")
			{
				CHECK(output.str() == "Draw text 'Hello world!' with font size 14 in (1, 1)\n");
			}
		}
	}
}
