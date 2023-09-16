#pragma once
#include "Point.h"
#include "Color.h"
#include <vector>
#include <string>

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void MoveTo(Point point) = 0;
	virtual void LineTo(Point point) = 0;
	virtual void SetColor(Color color) = 0;
	virtual void DrawEllipse(Point center, double rx, double ry) = 0;
	virtual void DrawText(Point leftTop, double fontSize, std::string text) = 0;
	virtual void Render() = 0;
};