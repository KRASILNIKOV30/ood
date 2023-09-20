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

std::string TriangleDrawingStrategy::GetType() const
{
	return "triangle";
}

ShapeParameters TriangleDrawingStrategy::GetParams() const
{
	return ShapeParameters{ {m_vertex1.x, m_vertex1.y, m_vertex2.x, m_vertex2.y, m_vertex3.x, m_vertex3.y} };
}

void TriangleDrawingStrategy::Move(Point vector)
{
	m_vertex1 += vector;
	m_vertex2 += vector;
	m_vertex3 += vector;
}
