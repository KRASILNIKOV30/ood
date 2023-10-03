#pragma once
#define _USE_MATH_DEFINES
#include <corecrt_math_defines.h>
#include "CShape.h"

class CRegulaPolygon final : public CShape
{
public:
	CRegulaPolygon(const Point m_center, const double radius, const unsigned m_vertex_count, const Color color)
		: CShape(color),
		  m_center(m_center),
		  m_radius(radius),
		  m_vertexCount(m_vertex_count)
	{
	}

private:
	void DrawLayout(ICanvas& canvas) override
	{
		const double dAngle = 2 * M_PI / m_vertexCount;
		Point prev = m_center + Point{ m_radius, 0 };
		double angle = dAngle;

		for (int i = 0; i < m_vertexCount; i++)
		{
			const Point curr = m_center + Point{std::cos(angle) * m_radius, std::sin(angle) * m_radius};
			canvas.DrawLine(prev, curr);
			prev = curr;
			angle += dAngle;
		}
	}

	Point m_center;
	double m_radius;
	unsigned int m_vertexCount;
};