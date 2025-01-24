#include "Selection.h"

constexpr int BORDER_WIDTH = 2;
constexpr int POINT_WIDTH = 16;

void Selection::Draw(wxDC& dc, const Frame& frame)
{
	m_frame = frame;
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

ScopedConnection Selection::DoOnReframe(const ReframeSlot& slot)
{
	return m_reframeSignal.connect(slot);
}

ScopedConnection Selection::DoOnApplyReframe(const ReframeSlot& slot)
{
	return m_applyReframeSignal.connect(slot);
}

bool Selection::CheckMouseDown(Point p)
{
	const auto [position, size] = m_frame;
	const auto [x, y] = position;
	const auto [width, height] = size;

	wxRegion region = wxRegion(x, y, width, height);

	wxRegion topLeft(x - POINT_WIDTH, y - POINT_WIDTH, POINT_WIDTH * 2, POINT_WIDTH * 2);
	wxRegion topRight(x + width - POINT_WIDTH, y - POINT_WIDTH, POINT_WIDTH * 2, POINT_WIDTH * 2);
	wxRegion bottomLeft(x - POINT_WIDTH, y + height - POINT_WIDTH, POINT_WIDTH * 2, POINT_WIDTH * 2);
	wxRegion bottomRight(x + width - POINT_WIDTH, y + height - POINT_WIDTH, POINT_WIDTH * 2, POINT_WIDTH * 2);

	wxRegion top(x, y - POINT_WIDTH, width, POINT_WIDTH * 2);
	wxRegion bottom(x, y + height - POINT_WIDTH, width, POINT_WIDTH * 2);
	wxRegion left(x - POINT_WIDTH, y, POINT_WIDTH * 2, height);
	wxRegion right(x + width - POINT_WIDTH, y, POINT_WIDTH * 2, height);

	m_startPoint = p;
	if (topLeft.Contains(p.x, p.y) == wxInRegion)
	{
		m_resizeType = ResizeType::TopLeft;
		return true;
	}
	if (topRight.Contains(p.x, p.y) == wxInRegion)
	{
		m_resizeType = ResizeType::TopRight;
		return true;
	}
	if (bottomLeft.Contains(p.x, p.y) == wxInRegion)
	{
		m_resizeType = ResizeType::BottomLeft;
		return true;
	}
	if (bottomRight.Contains(p.x, p.y) == wxInRegion)
	{
		m_resizeType = ResizeType::BottomRight;
		return true;
	}
	if (top.Contains(p.x, p.y) == wxInRegion)
	{
		m_resizeType = ResizeType::Top;
		return true;
	}
	if (bottom.Contains(p.x, p.y) == wxInRegion)
	{
		m_resizeType = ResizeType::Bottom;
		return true;
	}
	if (left.Contains(p.x, p.y) == wxInRegion)
	{
		m_resizeType = ResizeType::Left;
		return true;
	}
	if (right.Contains(p.x, p.y) == wxInRegion)
	{
		m_resizeType = ResizeType::Right;
		return true;
	}
	if (region.Contains(p.x, p.y) == wxInRegion)
	{
		m_resizeType = ResizeType::Free;
		return true;
	}
	m_startPoint.reset();

	return false;
}

void Selection::MouseMove(Point p)
{
	if (!m_startPoint.has_value())
	{
		return;
	}
	const auto start = m_startPoint.value();
	const auto delta = p - start;
	const auto newFrame = Reframe(delta);
	m_reframeSignal(newFrame);
	m_startPoint = p;
}

void Selection::MouseUp(Point p)
{
	if (!m_startPoint.has_value())
	{
		return;
	}
	const auto start = m_startPoint.value();
	const auto delta = p - start;
	const auto newFrame = Reframe(delta);
	m_reframeSignal(newFrame);
	m_applyReframeSignal(newFrame);
	m_startPoint.reset();
}

Frame Selection::Reframe(const Point delta) const
{
	const auto [position, size] = m_frame;
	switch (m_resizeType)
	{
	case ResizeType::TopLeft:
		return ResizeFrame(size, position, -delta.x, -delta.y, delta.x, delta.y);
	case ResizeType::TopRight:
		return ResizeFrame(size, position, delta.x, -delta.y, 0, delta.y);
	case ResizeType::BottomLeft:
		return ResizeFrame(size, position, -delta.x, delta.y, delta.x, 0);
	case ResizeType::BottomRight:
		return ResizeFrame(size, position, delta.x, delta.y, 0, 0);
	case ResizeType::Top:
		return ResizeFrame(size, position, 0, -delta.y, 0, delta.y);
	case ResizeType::Bottom:
		return ResizeFrame(size, position, 0, delta.y, 0, 0);
	case ResizeType::Left:
		return ResizeFrame(size, position, -delta.x, 0, delta.x, 0);
	case ResizeType::Right:
		return ResizeFrame(size, position, delta.x, 0, 0, 0);
	case ResizeType::Free:
		return ResizeFrame(size, position, 0, 0, delta.x, delta.y);
	}

	throw std::invalid_argument("Invalid resize type");
}

Frame Selection::ResizeFrame(const Size& _size, const Point& _position, int widthChange, int heightChange, int xChange, int yChange)
{
	Size size = { _size.width + widthChange, _size.height + heightChange };
	Point position = { _position.x + xChange, _position.y + yChange };

	if (size.width < 0)
	{
		position.x += size.width;
		size.width = std::abs(size.width);
	}

	if (size.height < 0)
	{
		position.y += size.height;
		size.height = std::abs(size.height);
	}

	return { position, size };
}
