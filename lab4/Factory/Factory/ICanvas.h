#pragma once
#include "Point.h"
#include "Color.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void DrawLine(Point from, Point to) = 0;
	virtual void SetColor(Color color) = 0;
	virtual void DrawEllipse(Point leftTop, double w, double h) = 0;
};