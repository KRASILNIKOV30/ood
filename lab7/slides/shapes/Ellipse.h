#pragma once
#include "Shape.h"
#include "../Clonable.h"

class Ellipse final : public Clonable<Shape, IShape, Ellipse, Frame const&, Color const&, Color const&>
{
public:
	Ellipse(Frame const& frame, Color const fillColor, Color const lineColor)
		: Clonable(frame, fillColor, lineColor)
	{}

	void DrawShape(const ICanvasPtr canvas) const override
	{
		canvas->DrawEllipse(GetFrame());
	}
};