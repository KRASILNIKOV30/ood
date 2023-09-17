#include "CircleDrawingStrategy.h"

CircleDrawingStrategy::CircleDrawingStrategy(Point center, double radius)
	: m_center(center)
	, m_radius(radius)
{
}

void CircleDrawingStrategy::Draw(ICanvas& canvas) const
{
	canvas.DrawEllipse(m_center, m_radius, m_radius);
}
