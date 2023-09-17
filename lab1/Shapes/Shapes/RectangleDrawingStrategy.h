#pragma once
#include "IDrawingStrategy.h"
class RectangleDrawingStrategy : public IDrawingStrategy
{
public:
	RectangleDrawingStrategy(Point leftTop, double width, double height);
	void Draw(ICanvas& canvas) const final;

private:
	Point m_leftTop;
	double m_width;
	double m_height;
};

