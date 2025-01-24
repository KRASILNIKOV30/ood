#pragma once
#include "../ShapeView.h"

class TriangleView final : public ShapeView
{
public:
	explicit TriangleView(const IShapeViewModelPtr& shape)
		: ShapeView(shape)
		, m_frame(shape->GetFrame())
	{
	}

	void Draw(wxDC& dc) const override
	{
		const auto points = GetPoints();
		dc.DrawPolygon(3, points);
	}

	[[nodiscard]] bool HitTest(const Point p) const override
	{
		const auto points = GetPoints();
		const wxRegion region(3, points);
		return region.Contains(p.x, p.y) == wxInRegion;
	}

private:
	[[nodiscard]] wxPoint* GetPoints() const
	{
		const auto [position, size] = m_frame;
		const auto [x, y] = position;
		const auto [width, height] = size;

		static wxPoint points[3] = {
			{ x + width / 2, y },
			{ x, y + height },
			{ x + width, y + height }
		};

		return points;
	}

private:
	Frame m_frame;
};
