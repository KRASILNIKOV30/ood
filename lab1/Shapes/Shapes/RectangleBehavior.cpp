#include "RectangleBehavior.h"

RectangleBehavior::RectangleBehavior(Point leftTop, double width, double height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void RectangleBehavior::Draw(ICanvas& canvas) const
{
	canvas.MoveTo(m_leftTop);
	canvas.LineTo(m_leftTop + Point{ m_width, 0 });
	canvas.LineTo(m_leftTop + Point{ m_width, m_height });
	canvas.LineTo(m_leftTop + Point{ 0, m_height });
	canvas.LineTo(m_leftTop);

}

std::string RectangleBehavior::GetType() const
{
	return "rectangle";
}

ShapeParameters RectangleBehavior::GetParams() const
{
	return ShapeParameters{ {m_leftTop.x, m_leftTop.y, m_width, m_height} };
}

void RectangleBehavior::Move(double dx, double dy)
{
	m_leftTop.x += dx;
	m_leftTop.y += dy;
}
