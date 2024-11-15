#pragma once
#include "Shape.h"

class Triangle final : public Shape
{
public:
	Triangle(Frame const& frame, Color const fillColor, Color const lineColor)
		: Shape(frame, fillColor, lineColor)
	{}

	void DrawShape(const ICanvasPtr canvas) const override
	{
		const auto [leftTop, width, height] = GetFrame();
		canvas->DrawPolygon({
			leftTop + Point{ width / 2, 0 },
			leftTop + Point{ width, height },
			leftTop + Point{ 0, height },
		});
	}
};