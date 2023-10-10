#include "../../../external/catch2/catch.hpp"
#include "../Factory/CEllipse.h"
#include "../Factory/CPictureDraft.h"
#include "../Factory/CRectangle.h"
#include "../Factory/CRegularPolygon.h"
#include "../Factory/CTriangle.h"

SCENARIO("Picture draft tests")
{
	GIVEN("Some shapes")
	{
		CRectangle rect(Point{ 3, 3 }, 10, 8, Color::Green);
		CTriangle triangle(Point{ 1, 1 }, Point{ 2, 2 }, Point{ 3, 3 }, Color::Yellow);
		CEllipse ellipse(Point{ 1, 1 }, 5, 3, Color::Pink);
		CRegularPolygon polygon(Point{ 5, 5 }, 5, 4, Color::Blue);
		Shapes shapes =
		{
			std::make_shared<CRectangle>(rect),
			std::make_shared<CTriangle>(triangle),
			std::make_shared<CEllipse>(ellipse),
			std::make_shared<CRegularPolygon>(polygon)
		};

		WHEN("Create picture draft with this shapes")
		{
			CPictureDraft draft(std::move(shapes));

			THEN("Draft can represent number of shapes")
			{
				//Протестировать получение фигуры по индексы вне массива
				CHECK(draft.GetShapeCount() == 4);
			}

			AND_THEN("Dratf can provide shapes")
			{
				auto const shape = draft.GetShape(2).get();
				CHECK_NOTHROW(dynamic_cast<CEllipse*>(shape));
				CHECK(shape->GetColor() == Color::Pink);
			}

			AND_THEN("Draft can throw out of range exception while getting non existing shape")
			{
				CHECK_THROWS_AS(draft.GetShape(4), std::out_of_range);
			}
		}
	}
}