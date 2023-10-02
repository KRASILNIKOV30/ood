#pragma once
#include "Color.h"
#include "ICanvas.h"

class CShape
{
public:
	explicit CShape(const Color color)
		: m_color(color)
	{
	}

	virtual ~CShape() = default;
	virtual void Draw(ICanvas& canvas) = 0;

	Color GetColor() const
	{
		return m_color;
	}

private:
	Color m_color;
};