#pragma once
#include <vector>
#include "../point/Point.h"
#include "../Color.h"
#include "../Frame.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	
	virtual void SetFillColor(Color color) = 0;
	virtual void SetLineColor(Color color) = 0;
	virtual void SetLineWidth(double width) = 0;
	virtual void DrawLine(Point from, Point to) = 0;
	virtual void DrawEllipse(Frame frame) = 0;
	virtual void DrawPolygon(std::vector<Point> points) = 0;
};
