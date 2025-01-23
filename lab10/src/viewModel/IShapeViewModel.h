#pragma once
#include "../Frame.h"
#include "../signals/SignallingValue.h"
#include <string>

#include <memory>

class IShapeViewModel
{
public:
	using ClickSignal = EmptySignal;
	using ClickSignalSlot = ClickSignal::slot_type;

	[[nodiscard]] virtual std::string GetId() const = 0;
	[[nodiscard]] virtual Frame GetFrame() const = 0;
	[[nodiscard]] virtual std::string GetType() const = 0;

	virtual void SetSelected(bool selected) = 0;
	virtual void Click() = 0;
	// virtual void Drag(Point p) = 0;
	// virtual void Drop(Point p) = 0;
	virtual ScopedConnection DoOnClick(ClickSignalSlot const& slot) = 0;

	virtual ~IShapeViewModel() = default;
};

using IShapeViewModelPtr = std::shared_ptr<IShapeViewModel>;