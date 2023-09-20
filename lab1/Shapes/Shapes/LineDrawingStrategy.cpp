#include "LineDrawingStrategy.h"

LineDrawingStrategy::LineDrawingStrategy(Point start, Point end)
	: m_start(start)
	, m_end(end)
{
}

void LineDrawingStrategy::Draw(ICanvas& canvas) const
{
	canvas.MoveTo(m_start);
	canvas.LineTo(m_end);
}

std::string LineDrawingStrategy::GetType() const
{
	return "line";
}

ShapeParameters LineDrawingStrategy::GetParams() const
{
	return ShapeParameters{ {m_start.x, m_start.y, m_end.x, m_end.y} };
}

void LineDrawingStrategy::Move(Point vector)
{
	m_start += vector;
	m_end += vector;
}
