#pragma once
#include "IDrawingStrategy.h"

class CircleDrawingStrategy : public IDrawingStrategy
{
public:
	CircleDrawingStrategy(Point center, double radius);
	void Draw(ICanvas& canvas) const final;

private:
	Point m_center;
	double m_radius;
};

