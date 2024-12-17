#pragma once
#include "../signals/SignallingValue.h"
#include "Shape.h"

#include <functional>

class IShapes
{
public:
	using AddShapeSignal = Signal<void(IShape* shape, size_t position)>;
	using RemoveShapeSignal = Signal<void(std::string const& id)>;
	using AddShapeSlot = AddShapeSignal::slot_type;
	using RemoveShapeSlot = RemoveShapeSignal::slot_type;

	virtual void AddShape(IShapePtr&& shape, std::optional<size_t> position) = 0;
	virtual size_t RemoveShape(std::string const& id) = 0;

	[[nodiscard]] virtual const IShape* GetShape(std::string const& id) const = 0;
	[[nodiscard]] virtual IShape* GetShape(std::string const& id) = 0;
	[[nodiscard]] virtual size_t GetSize() const = 0;
	virtual void ForEach(std::function<bool(const IShape*)> callback) const = 0;

	virtual ScopedConnection DoOnAddShape(AddShapeSlot const& slot) = 0;
	virtual ScopedConnection DoOnRemoveShape(RemoveShapeSlot const& slot) = 0;

	virtual ~IShapes() = default;
};