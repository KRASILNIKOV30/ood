#pragma once
#include "Shape.h"
#include "../Clonable.h"

class Triangle final : public Clonable<Shape, IShape, Triangle, Frame const&, Color const, Color const>
{
public:
	Triangle(Frame const& frame, Color const fillColor, Color const lineColor)
		: Clonable(frame, std::move(fillColor), std::move(lineColor))
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