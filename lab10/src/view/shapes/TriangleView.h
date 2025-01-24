#pragma once
#include "../ShapeView.h"

class TriangleView final : public ShapeView
{
public:
	explicit TriangleView(const IShapeViewModelPtr& shape)
		: ShapeView(shape)
	{
	}

	void Draw(wxDC& dc) const override
	{
		dc.SetPen(wxPen(*wxBLACK));
		dc.SetBrush(*wxRED);

		const auto [position, size] = GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		wxPoint points[3] = {
			{ x + width / 2, y },
			{ x, y + height },
			{ x + width, y + height }
		};

		dc.DrawPolygon(3, points);
	}

	[[nodiscard]] bool HitTest(const Point p) const override
	{
		const auto [position, size] = GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		wxPoint points[3] = {
			{ x + width / 2, y },
			{ x, y + height },
			{ x + width, y + height }
		};

		const wxRegion region(3, points);
		return region.Contains(p.x, p.y) == wxInRegion;
	}
};
