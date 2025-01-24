#pragma once
#include "../ShapeView.h"

class EllipseView final : public ShapeView
{
public:
	explicit EllipseView(const IShapeViewModelPtr& shape)
		: ShapeView(shape)
	{
	}

	void Draw(wxDC& dc) const override
	{
		dc.SetPen(wxPen(*wxBLACK));
		dc.SetBrush(*wxGREY_BRUSH);

		const auto [position, size] = GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		dc.DrawEllipse(x, y, width, height);
	}

	[[nodiscard]] bool HitTest(const Point p) const override
	{
		const auto [position, size] = GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		const double a = width / 2.0;
		const double b = height / 2.0;

		const double centerX = x + a;
		const double centerY = y + b;

		const double dx = p.x - centerX;
		const double dy = p.y - centerY;

		return (dx * dx) / (a * a) + (dy * dy) / (b * b) <= 1.0;
	}
};
