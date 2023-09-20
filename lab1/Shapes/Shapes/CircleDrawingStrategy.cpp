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

std::string CircleDrawingStrategy::GetType() const
{
	return "circle";
}

ShapeParameters CircleDrawingStrategy::GetParams() const
{
	return ShapeParameters{ {m_center.x, m_center.y, m_radius} };
}

void CircleDrawingStrategy::Move(Point vector)
{
	m_center += vector;
}
