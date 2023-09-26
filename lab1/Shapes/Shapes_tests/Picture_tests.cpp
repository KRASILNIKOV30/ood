#include "../../../external/catch2/catch.hpp"
#include "MockCanvasFixture.h"
#include "../Shapes/Picture.h"
#include <vector>
#include "../Shapes/ShapeParameters.h"
#include "../Shapes/TriangleBehavior.h"
#include "../Shapes/CircleBehavior.h"
#include "../Shapes/LineBehavior.h"
#include "../Shapes/RectangleBehavior.h"
#include "../Shapes/TextBehavior.h"

SCENARIO("Add and list shape")
{
	GIVEN("Some picture")
	{
		Picture picture;

		THEN("Picture has no figures")
		{
			CHECK(picture.ListShapes() == "");
		}

		WHEN("Add shape")
		{
			CHECK(picture.AddShape("1", 0, ShapeType::CIRCLE, std::make_unique<CircleBehavior>(Point{ 5, 7 }, 3)));


			THEN("Picture has one shape")
			{
				CHECK(picture.ListShapes() == "1. circle 1 #000000 5 7 3\n");
			}

			AND_WHEN("Add another shapes")
			{
				CHECK(picture.AddShape("2", 0, ShapeType::TRIANGLE, std::make_unique<TriangleBehavior>(Point{ 1, 1 }, Point{ 2, 2 }, Point{ 3, 3 })));
				CHECK(picture.AddShape("3", 0, ShapeType::TEXT, std::make_unique<TextBehavior>(Point{ 6, 8 }, 14.5, "Hello world")));

				THEN("Picture list shapes in correct order")
				{
					CHECK(picture.ListShapes() ==
						"1. circle 1 #000000 5 7 3\n"
						"2. triangle 2 #000000 1 1 2 2 3 3\n"
						"3. text 3 #000000 6 8 14.5 Hello world\n"
					);
				}
			}
		}
	}
}

SCENARIO("Move shapes")
{
	GIVEN("Picture with all type of shapes")
	{
		Picture picture;
		CHECK(picture.AddShape("cr", 0, ShapeType::CIRCLE, std::make_unique<CircleBehavior>(Point{ 5, 7 }, 3)));
		CHECK(picture.AddShape("tr", 0, ShapeType::TRIANGLE, std::make_unique<TriangleBehavior>(Point{ 1, 1 }, Point{ 2, 2 }, Point{ 3, 3 })));
		CHECK(picture.AddShape("txt", 0, ShapeType::TEXT, std::make_unique<TextBehavior>(Point{ 6, 8 }, 14.5, "Hello world")));
		CHECK(picture.AddShape("ln", 0, ShapeType::LINE, std::make_unique<LineBehavior>(Point{ 1,2 }, Point{ 3, 4 })));
		CHECK(picture.AddShape("rc", 0, ShapeType::RECTANGLE, std::make_unique<RectangleBehavior>(Point{ 10, 10 }, 12, 4)));

		WHEN("Move shape with id cr")
		{
			picture.MoveShape("cr", 2, 3);

			THEN("One shape has been moved")
			{
				CHECK(picture.ListShapes() ==
					"1. circle cr #000000 7 10 3\n"
					"2. triangle tr #000000 1 1 2 2 3 3\n"
					"3. text txt #000000 6 8 14.5 Hello world\n"
					"4. line ln #000000 1 2 3 4\n"
					"5. rectangle rc #000000 10 10 12 4\n"
				);
			}

			AND_WHEN("Move picture")
			{
				picture.MovePicture(1, 1);

				THEN("All shapes has been moved")
				{
					CHECK(picture.ListShapes() ==
						"1. circle cr #000000 8 11 3\n"
						"2. triangle tr #000000 2 2 3 3 4 4\n"
						"3. text txt #000000 7 9 14.5 Hello world\n"
						"4. line ln #000000 2 3 4 5\n"
						"5. rectangle rc #000000 11 11 12 4\n"
					);
				}
			}
			
		}

		WHEN("Move shape witn id that is not exist")
		{
			CHECK_FALSE(picture.MoveShape("not-existing-id", 1, 1));

			THEN("No one shape has benn moved")
			{
				CHECK(picture.ListShapes() ==
					"1. circle cr #000000 5 7 3\n"
					"2. triangle tr #000000 1 1 2 2 3 3\n"
					"3. text txt #000000 6 8 14.5 Hello world\n"
					"4. line ln #000000 1 2 3 4\n"
					"5. rectangle rc #000000 10 10 12 4\n"
				);
			}
		}
	}
}

SCENARIO("Delete shape")
{
	GIVEN("Picture with 3 shapes")
	{
		Picture picture;
		CHECK(picture.AddShape("cr", 0, ShapeType::CIRCLE, std::make_unique<CircleBehavior>(Point{ 5, 7 }, 3)));
		CHECK(picture.AddShape("tr", 0, ShapeType::TRIANGLE, std::make_unique<TriangleBehavior>(Point{ 1, 1 }, Point{ 2, 2 }, Point{ 3, 3 })));
		CHECK(picture.AddShape("txt", 0, ShapeType::TEXT, std::make_unique<TextBehavior>(Point{ 6, 8 }, 14.5, "Hello world")));

		WHEN("Delete shape in the middle")
		{
			CHECK(picture.DeleteShape("tr"));

			THEN("Shape has been deleted")
			{
				CHECK(picture.ListShapes() ==
					"1. circle cr #000000 5 7 3\n"
					"2. text txt #000000 6 8 14.5 Hello world\n"
				);
			}
		}

		WHEN("Delete shape witn id that is not exist")
		{
			CHECK_FALSE(picture.DeleteShape("not-existing-id"));

			THEN("No one shape has benn deleted")
			{
				CHECK(picture.ListShapes() ==
					"1. circle cr #000000 5 7 3\n"
					"2. triangle tr #000000 1 1 2 2 3 3\n"
					"3. text txt #000000 6 8 14.5 Hello world\n"
				);
			}
		}
	}
}

SCENARIO("Change shapes color")
{
	GIVEN("Picture with one black shape")
	{
		Picture picture;
		CHECK(picture.AddShape("cr", 0, ShapeType::CIRCLE, std::make_unique<CircleBehavior>(Point{ 5, 7 }, 3)));

		WHEN("Change shapes color")
		{
			CHECK(picture.ChangeColor("cr", 15));

			THEN("Color has been changed")
			{
				CHECK(picture.ListShapes() == "1. circle cr #00000f 5 7 3\n");
			}
		}

		WHEN("Change color of shape with id that is not exist")
		{
			CHECK_FALSE(picture.ChangeColor("not-existing-id", 15));

			THEN("Color has not been changed")
			{
				CHECK(picture.ListShapes() == "1. circle cr #000000 5 7 3\n");
			}
		}
	}
}

SCENARIO("Change shape")
{
	GIVEN("Picture with circle")
	{
		Picture picture;
		CHECK(picture.AddShape("cr", 0, ShapeType::CIRCLE, std::make_unique<CircleBehavior>(Point{ 5, 7 }, 3)));

		WHEN("Change shape")
		{
			CHECK(picture.ChangeShape("cr", ShapeType::RECTANGLE, std::make_unique<RectangleBehavior>(Point{ 10, 10 }, 12, 4)));

			THEN("Shape has been changed")
			{
				CHECK(picture.ListShapes() == "1. rectangle cr #000000 10 10 12 4\n");
			}
		}

		WHEN("Change shape with id that is not exist")
		{
			CHECK_FALSE(picture.ChangeShape("not-existing-id", ShapeType::RECTANGLE, std::make_unique<RectangleBehavior>(Point{ 10, 10 }, 12, 4)));

			THEN("Shape has not been changed")
			{
				CHECK(picture.ListShapes() == "1. circle cr #000000 5 7 3\n");
			}
		}
	}
}

SCENARIO_METHOD(MockCanvasFixture, "Drawing")
{
	GIVEN("Picture with all type of shapes")
	{
		Picture picture;
		CHECK(picture.AddShape("cr", 0, ShapeType::CIRCLE, std::make_unique<CircleBehavior>(Point{ 5, 7 }, 3)));
		CHECK(picture.AddShape("tr", 0, ShapeType::TRIANGLE, std::make_unique<TriangleBehavior>(Point{ 1, 1 }, Point{ 2, 2 }, Point{ 3, 3 })));
		CHECK(picture.AddShape("txt", 0, ShapeType::TEXT, std::make_unique<TextBehavior>(Point{ 6, 8 }, 14.5, "Hello world")));
		CHECK(picture.AddShape("ln", 0, ShapeType::LINE, std::make_unique<LineBehavior>(Point{ 1,2 }, Point{ 3, 4 })));
		CHECK(picture.AddShape("rc", 0, ShapeType::RECTANGLE, std::make_unique<RectangleBehavior>(Point{ 10, 10 }, 12, 4)));

		WHEN("Draw one shape")
		{
			CHECK(picture.DrawShape("cr", mockCanvas.get()));

			THEN("Circle has been drawn at canvas")
			{
				CHECK(output.str() == "Set color 0\nDraw ellipse in (5, 7) with rx 3 and ry 3\n");
			}
		}

		WHEN("Draw shape with id that is not exist")
		{
			CHECK_FALSE(picture.DrawShape("not-existing-id", mockCanvas.get()));

			THEN("Nothing has been drawn at canvas")
			{
				CHECK(output.str().empty());
			}
		}

		WHEN("Draw picture")
		{
			picture.DrawPicture(mockCanvas.get());

			THEN("All shapes has been drawn at canvas")
			{
				CHECK(output.str() ==
					//ellipse
					"Set color 0\nDraw ellipse in (5, 7) with rx 3 and ry 3\n"

					//triangle
					"Set color 0\n"
					"Move to (1, 1)\n"
					"Line to (2, 2)\n"
					"Line to (3, 3)\n"
					"Line to (1, 1)\n"

					//text
					"Set color 0\n"
					"Draw text 'Hello world' with font size 14.5 in (6, 8)\n"

					//line
					"Set color 0\n"
					"Move to (1, 2)\n"
					"Line to (3, 4)\n"

					//rectangle
					"Set color 0\n"
					"Move to (10, 10)\n"
					"Line to (22, 10)\n"
					"Line to (22, 14)\n"
					"Line to (10, 14)\n"
					"Line to (10, 10)\n"
				);
			}
		}
	}
}
