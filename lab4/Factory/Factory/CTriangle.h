#pragma once
#include "CShape.h"

class CTriangle final : public CShape
{
public:
	CTriangle(const Point& vertex1, const Point& vertex2, const Point& vertex3, const Color color)
		: CShape(color),
		  m_vertex1(vertex1),
		  m_vertex2(vertex2),
		  m_vertex3(vertex3)
	{
	}

	Point GetVertex1() const
	{
		return m_vertex1;
	}

	Point GetVertex2() const
	{
		return m_vertex2;
	}

	Point GetVertex3() const
	{
		return m_vertex3;
	}

private:
	void DrawLayout(ICanvas& canvas) const override
	{
		canvas.DrawLine(m_vertex1, m_vertex2);
		canvas.DrawLine(m_vertex2, m_vertex3);
		canvas.DrawLine(m_vertex3, m_vertex1);
	}

	Point m_vertex1, m_vertex2, m_vertex3;
};
