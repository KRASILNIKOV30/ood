#pragma once
#include "Shape.h"
#include "../Clonable.h"

class Circle final : public Clonable<Shape, IShape, Circle, Frame const&, Color const&, Color const&>
{
public:
	Circle(Frame const& frame, Color const& fillColor, Color const& lineColor)
		: Clonable(frame, fillColor, lineColor)
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