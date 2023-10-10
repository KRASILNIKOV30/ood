#include "../../../external/catch2/catch.hpp"
#include "../Factory/Common.h"
#include "../Factory/CPictureDraft.h"
#include "../Factory/CShape.h"
#include <iostream>

#include "../Factory/CPainter.h"
#include "../Factory/MockCanvas.h"

namespace
{
	class MockShape final : public CShape
	{
	public:
		explicit MockShape(const Color color)
			: CShape(color)
		{
		}

	private:
		void DrawLayout(ICanvas& canvas) const override
		{
			std::cout << "Draw shape" << std::endl;
		}
	};
}


SCENARIO_METHOD(CoutBufferFixture, "Painter tests")
{
	GIVEN("Shapes draft")
	{
		Shapes shapes =
		{
			std::make_shared<MockShape>(Color::Yellow),
			std::make_shared<MockShape>(Color::Black)
		};
		const CPictureDraft draft(std::move(shapes));

		AND_GIVEN("Painter")
		{
			constexpr CPainter painter;

			WHEN("Painter draws picture by draft")
			{
				MockCanvas canvas;
				painter.DrawPicture(draft, canvas);

				THEN("Painter draws all shapes")
				{
					CHECK(GetOutput() ==
						"Set color yellow\n"
						"Draw shape\n"
						"Set color black\n"
						"Draw shape\n"
					);
				}
			}
		}
	}
}
