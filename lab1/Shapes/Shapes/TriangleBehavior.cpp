#include "TriangleBehavior.h"

TriangleBehavior::TriangleBehavior(Point vertex1, Point vertex2, Point vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

void TriangleBehavior::Draw(ICanvas& canvas) const
{
	canvas.MoveTo(m_vertex1);
	canvas.LineTo(m_vertex2);
	canvas.LineTo(m_vertex3);
	canvas.LineTo(m_vertex1);
}

std::string TriangleBehavior::GetType() const
{
	return "triangle";
}

ShapeParameters TriangleBehavior::GetParams() const
{
	return ShapeParameters{ {m_vertex1.x, m_vertex1.y, m_vertex2.x, m_vertex2.y, m_vertex3.x, m_vertex3.y} };
}

void TriangleBehavior::Move(double dx, double dy)
{
	m_vertex1.x += dx;
	m_vertex2.x += dx;
	m_vertex3.x += dx;
	m_vertex1.y += dy;
	m_vertex2.y += dy;
	m_vertex3.y += dy;
}
