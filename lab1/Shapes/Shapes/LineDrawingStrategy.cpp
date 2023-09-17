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
