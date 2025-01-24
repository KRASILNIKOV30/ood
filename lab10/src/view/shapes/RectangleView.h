#pragma once
#include "../ShapeView.h"

class RectangleView final : public ShapeView
{
public:
	explicit RectangleView(const IShapeViewModelPtr& shape)
		: ShapeView(shape)
		, m_frame(shape->GetFrame())
	{
	}

	void Draw(wxDC& dc) const override
	{
		const auto [position, size] = m_frame;
		const auto [x, y] = position;
		const auto [width, height] = size;

		dc.DrawRectangle(x, y, width, height);
	}

	[[nodiscard]] bool HitTest(Point p) const override
	{
		const auto [position, size] = m_frame;
		const auto [x, y] = position;
		const auto [width, height] = size;

		return (p.x >= x && p.x <= x + width && p.y >= y && p.y <= y + height);
	}

private:
	Frame m_frame;
};