#pragma once
#include "../Frame.h"
#include "../signals/SignallingValue.h"
#include <memory>
#include <string>

using ReframeSignal = Signal<void(Frame const& frame)>;
using ReframeSlot = ReframeSignal::slot_type;

class IShape
{
public:
	virtual void Reframe(Frame const& frame) = 0;
	virtual ScopedConnection DoOnReframe(ReframeSlot const& slot) = 0;

	[[nodiscard]] virtual Frame GetFrame() const = 0;
	[[nodiscard]] virtual std::string GetType() const = 0;
	[[nodiscard]] virtual std::string GetId() const = 0;

	virtual ~IShape() = default;
};

using IShapePtr = std::shared_ptr<IShape>;