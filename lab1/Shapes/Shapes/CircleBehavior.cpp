#include "CircleBehavior.h"

CircleBehavior::CircleBehavior(Point center, double radius)
	: m_center(center)
	, m_radius(radius)
{
}

void CircleBehavior::Draw(ICanvas& canvas) const
{
	canvas.DrawEllipse(m_center, m_radius, m_radius);
}

std::string CircleBehavior::GetType() const
{
	return "circle";
}

ShapeParameters CircleBehavior::GetParams() const
{
	return ShapeParameters{ {m_center.x, m_center.y, m_radius} };
}

void CircleBehavior::Move(double dx, double dy)
{
	m_center.x += dx;
	m_center.y += dy;
}
