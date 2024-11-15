#pragma once
#include "Shape.h"

class Rectangle final : public Shape
{
public:
	Rectangle(Frame const& frame, Color const fillColor, Color const lineColor)
		: Shape(frame, fillColor, lineColor)
	{}

	void DrawShape(const ICanvasPtr canvas) const override
	{
		const auto [leftTop, width, height] = GetFrame();
		canvas->DrawPolygon({
			leftTop,
			leftTop + Point{ width, 0 },
			leftTop + Point{ width, height },
			leftTop + Point{ 0, height },
		});
	}
};