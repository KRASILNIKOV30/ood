#pragma once
#include "../../Frame.h"
#include "../../signals/SignallingValue.h"

#include <memory>
#include <wx/wx.h>

class ISelection
{
public:
	using ReframeSignal = Signal<void(Frame const& frame)>;
	using ReframeSlot = ReframeSignal::slot_type;

	virtual void Draw(wxDC& dc, Frame const& frame) = 0;
	virtual ScopedConnection DoOnReframe(ReframeSlot const& slot) = 0;
	virtual ScopedConnection DoOnApplyReframe(ReframeSlot const& slot) = 0;
	[[nodiscard]] virtual bool CheckMouseDown(Point p) = 0;
	virtual void MouseMove(Point p) = 0;
	virtual void MouseUp(Point p) = 0;

	virtual ~ISelection() = default;
};

using ISelectionPtr = std::shared_ptr<ISelection>;
