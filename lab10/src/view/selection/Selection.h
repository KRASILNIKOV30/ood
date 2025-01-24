#pragma once
#include "../../ResizeType.h"
#include "../canvas/ICanvas.h"
#include "ISelection.h"

#include <optional>

class Selection final : public ISelection
{
public:
	void Draw(wxDC& dc, const Frame& frame) override;
	ScopedConnection DoOnReframe(const ReframeSlot& slot) override;
	ScopedConnection DoOnApplyReframe(const ReframeSlot& slot) override;
	[[nodiscard]] bool CheckMouseDown(Point p) override;
	void MouseMove(Point p) override;
	void MouseUp(Point p) override;

private:
	static Frame ResizeFrame(const Size& _size, const Point& _position,
		int widthChange, int heightChange,
		int xChange, int yChange);
	[[nodiscard]] Frame Reframe(Point delta) const;

private:
	ICanvasPtr m_canvas;
	ReframeSignal m_reframeSignal;
	ReframeSignal m_applyReframeSignal;
	ResizeType m_resizeType = ResizeType::Right;
	Frame m_frame;
	std::optional<Point> m_startPoint;
};