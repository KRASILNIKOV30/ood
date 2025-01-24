#include "Selection.h"

constexpr int BORDER_WIDTH = 2;
constexpr int POINT_WIDTH = 16;

void Selection::Draw(wxDC& dc, const Frame& frame)
{
	dc.SetPen(wxPen(*wxBLUE, BORDER_WIDTH));
	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	const auto [position, size] = frame;
	const auto [x, y] = position;
	const auto [width, height] = size;

	dc.DrawRectangle(x, y, width, height);

	dc.SetPen(wxPen(*wxBLUE, POINT_WIDTH));
	dc.DrawPoint(x, y);
	dc.DrawPoint(x + width, y);
	dc.DrawPoint(x, y + height);
	dc.DrawPoint(x + width, y + height);
	dc.SetPen(wxPen(*wxBLUE, BORDER_WIDTH));
}
