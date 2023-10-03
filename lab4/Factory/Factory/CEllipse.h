#pragma once
#include "CShape.h"

class CEllipse final : public CShape
{
public:
	CEllipse(const Point& m_left_top, const double m_width, const double m_height, const Color color)
		: CShape(color),
		  m_leftTop(m_left_top),
		  m_width(m_width),
		  m_height(m_height)
	{
	}

	Point GetCenter() const
	{
		return m_leftTop + Point{ m_width / 2, m_height / 2 };
	}

	double GetHorizontalRadius() const
	{
		return m_width / 2;
	}

	double GetVerticalRadius() const
	{
		return m_height / 2;
	}

private:
	void DrawLayout(ICanvas& canvas) override
	{
		canvas.DrawEllipse(m_leftTop, m_width, m_height);
	}

	Point m_leftTop;
	double m_width;
	double m_height;
};
