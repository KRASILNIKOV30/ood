#include "LineBehavior.h"

LineBehavior::LineBehavior(Point start, Point end)
	: m_start(start)
	, m_end(end)
{
}

void LineBehavior::Draw(ICanvas& canvas) const
{
	canvas.MoveTo(m_start);
	canvas.LineTo(m_end);
}

std::string LineBehavior::GetType() const
{
	return "line";
}

ShapeParameters LineBehavior::GetParams() const
{
	return ShapeParameters{ {m_start.x, m_start.y, m_end.x, m_end.y} };
}

void LineBehavior::Move(Point vector)
{
	m_start += vector;
	m_end += vector;
}
