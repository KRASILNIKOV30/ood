#include "../../../external/catch2/catch.hpp"
#include "../Factory/CShapeFactory.h"
#include "../Factory/MockCanvas.h"

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

SCENARIO_METHOD(CoutBufferFixture, "Shape factory tests")
{
	GIVEN("The factory")
	{
		const CShapeFactory factory;

		WHEN("Try to create a shape")
		{
			auto const shape = factory.CreateShape("rectangle 3 3 10 8 green");

			THEN("Factory creates shape with correct parameters")
			{
				CHECK_NOTHROW(dynamic_cast<CRectangle*>(shape.get()));
				CHECK(shape->GetColor() == Color::Green);
			}

			AND_THEN("Shape can be drawn")
			{
				MockCanvas canvas;
				shape->Draw(canvas);

				CHECK(GetOutput() ==
					"Set color green\n"
					"Draw line from (3, 3) to (13, 3)\n"
					"Draw line from (13, 3) to (13, 11)\n"
					"Draw line from (13, 11) to (3, 11)\n"
					"Draw line from (3, 11) to (3, 3)\n"
				);
			}
		}
	}
}