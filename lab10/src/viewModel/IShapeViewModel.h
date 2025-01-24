#pragma once
#include "../Frame.h"
#include "../model/IShape.h"
#include "../signals/SignallingValue.h"
#include <memory>
#include <string>

class IShapeViewModel
{
public:
	using ClickSignal = EmptySignal;
	using ClickSignalSlot = ClickSignal::slot_type;

	virtual ScopedConnection DoOnReframe(ReframeSlot const& slot) = 0;
	virtual ScopedConnection DoOnClick(ClickSignalSlot const& slot) = 0;

	[[nodiscard]] virtual std::string GetId() const = 0;
	[[nodiscard]] virtual Frame GetFrame() const = 0;
	[[nodiscard]] virtual std::string GetType() const = 0;

	virtual void Click(Point p) = 0;
	virtual void Drag(Point p) = 0;
	virtual void Drop(Point p) = 0;

	virtual void Reframe(Frame const& frame) = 0;
	virtual void ApplyReframe(Frame const& frame) = 0;

	virtual ~IShapeViewModel() = default;
};

using IShapeViewModelPtr = std::shared_ptr<IShapeViewModel>;