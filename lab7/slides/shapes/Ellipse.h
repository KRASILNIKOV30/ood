#pragma once
#include "Shape.h"

class Ellipse final : public Shape
{
public:
	Ellipse(Frame const& frame, Color const fillColor, Color const lineColor)
		: Shape(frame, fillColor, lineColor)
	{}

	void DrawShape(const ICanvasPtr canvas) const override
	{
		canvas->DrawEllipse(GetFrame());
	}
};