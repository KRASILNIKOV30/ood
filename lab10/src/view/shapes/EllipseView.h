#pragma once
#include "../ShapeView.h"

class EllipseView final : public ShapeView
{
public:
	explicit EllipseView(const IShapeViewModelPtr& shape)
		: ShapeView(shape)
		, m_frame(shape->GetFrame())
	{
	}

	void Draw(wxDC& dc) const override
	{
		const auto [position, size] = m_frame;
		const auto [x, y] = position;
		const auto [width, height] = size;

		dc.DrawEllipse(x, y, width, height);
	}

	[[nodiscard]] bool HitTest(const Point p) const override
	{
		const auto [position, size] = m_frame;
		const auto [x, y] = position;
		const auto [width, height] = size;

		const auto centerX = x + width / 2;
		const auto centerY = y + height / 2;

		return (((p.x - centerX) * (p.x - centerX)) / (width / 2) / (width / 2) + ((p.y - centerY) * (p.y - centerY)) / (height / 2) / (height / 2)) <= 1;
	}

private:
	Frame m_frame;
};
