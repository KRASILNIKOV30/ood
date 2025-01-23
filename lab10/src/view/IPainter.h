#pragma once
#include "../signals/SignallingValue.h"
#include "IShapeView.h"

class IPainter
{
public:
	using SelectionChangeSignal = Signal<void()>;
	using SelectionChangeSlot = SelectionChangeSignal::slot_type;

	virtual ScopedConnection DoOnSelectionChange(SelectionChangeSlot const& slot) = 0;
	virtual std::optional<IShapeViewPtr> GetSelectedShape() = 0;
	virtual void AddShape(std::string const& type) = 0;

	virtual ~IPainter() = default;
};

using IPainterPtr = std::shared_ptr<IPainter>;