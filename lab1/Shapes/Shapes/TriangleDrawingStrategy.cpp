#include "TriangleDrawingStrategy.h"

TriangleDrawingStrategy::TriangleDrawingStrategy(Point vertex1, Point vertex2, Point vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

void TriangleDrawingStrategy::Draw(ICanvas& canvas) const
{
	canvas.MoveTo(m_vertex1);
	canvas.LineTo(m_vertex2);
	canvas.LineTo(m_vertex3);
	canvas.LineTo(m_vertex1);
}
