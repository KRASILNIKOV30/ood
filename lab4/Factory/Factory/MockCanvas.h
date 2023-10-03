#pragma once
#include "ICanvas.h"

class MockCanvas final : public ICanvas
{
public:
	void DrawLine(const Point from, const Point to) override
	{
		std::cout << "Draw line from " << from << " to " << to << std::endl;
	}

	void SetColor(const Color color) override
	{
		std::cout << "Set color " << ColorToStr(color) << std::endl;
	}

	void DrawEllipse(const Point leftTop, const double w, const double h) override
	{
		std::cout << "Draw ellipse from " << leftTop << " with width " << w << " and height " << h << std::endl;
	}
};
