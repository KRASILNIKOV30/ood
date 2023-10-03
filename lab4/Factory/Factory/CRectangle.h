#pragma once
#include "CShape.h"
#include "Point.h"

class CRectangle final : public CShape
{
public:
	explicit CRectangle(const Point leftTop, const double width, const double height, const Color color)
		: CShape(color)
		, m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
	{
	}

	Point GetLeftTop() const
	{
		return m_leftTop;
	}

	Point GetRightBottom() const
	{
		return m_leftTop + Point{ m_width, m_height };
	}

private:
	void DrawLayout(ICanvas& canvas) override
	{
		canvas.DrawLine(m_leftTop, m_leftTop + Point{ m_width, 0 });
		canvas.DrawLine(m_leftTop + Point{ m_width, 0 }, m_leftTop + Point{ m_width, m_height });
		canvas.DrawLine(m_leftTop + Point{ m_width, m_height }, m_leftTop + Point{ 0, m_height });
		canvas.DrawLine(m_leftTop + Point{ 0, m_height }, m_leftTop);
	}

	Point m_leftTop;
	double m_width;
	double m_height;
};
