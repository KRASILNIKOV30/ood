#pragma once
#include "../signals/SignallingValue.h"
#include "Shape.h"

#include <functional>

class IShapes
{
public:
	using AddShapeSignal = Signal<void(IShapePtr shape, size_t position)>;
	using RemoveShapeSignal = Signal<void(std::string const& id)>;
	using AddShapeSlot = AddShapeSignal::slot_type;
	using RemoveShapeSlot = RemoveShapeSignal::slot_type;

	virtual std::string AddShape(std::string const& type) = 0;
	virtual void AddShape(IShapePtr const& shape, std::optional<size_t> position) = 0;
	virtual size_t RemoveShape(std::string const& id) = 0;
	virtual size_t RemoveLastShape() = 0;

	[[nodiscard]] virtual IShapePtr GetShape(std::string const& id) const = 0;
	[[nodiscard]] virtual IShapePtr GetShape(std::string const& id) = 0;
	[[nodiscard]] virtual size_t GetSize() const = 0;
	virtual void ForEach(std::function<bool(IShapePtr)> callback) const = 0;

	virtual ScopedConnection DoOnAddShape(AddShapeSlot const& slot) = 0;
	virtual ScopedConnection DoOnRemoveShape(RemoveShapeSlot const& slot) = 0;

	virtual ~IShapes() = default;
};
