#pragma once
#include "Point.h"
#include "Color.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void DrawLine(Point const from, Point const to) = 0;
	virtual void SetColor(Color const color) = 0;
	virtual void DrawEllipse(Point const leftTop, double const w, double const h) = 0;
};