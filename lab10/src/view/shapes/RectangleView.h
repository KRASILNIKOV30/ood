#pragma once
#include "../ShapeView.h"

class RectangleView final : public ShapeView
{
public:
	explicit RectangleView(const IShapeViewModelPtr& shape)
		: ShapeView(shape)
	{
	}

	void Draw(wxDC& dc) const override
	{
		dc.SetPen(wxPen(*wxBLACK));
		dc.SetBrush(*wxGREEN);

		const auto [position, size] = GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		dc.DrawRectangle(x, y, width, height);
	}

	[[nodiscard]] bool HitTest(Point p) const override
	{
		const auto [position, size] = GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		return (p.x >= x && p.x <= x + width && p.y >= y && p.y <= y + height);
	}
};