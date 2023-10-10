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

	void Draw(ICanvas& canvas) const
	{
		canvas.SetColor(m_color);
		DrawLayout(canvas);
	}

	Color GetColor() const
	{
		return m_color;
	}

private:
	virtual void DrawLayout(ICanvas& canvas) const = 0;
	Color m_color;
};