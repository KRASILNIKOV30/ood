#pragma once
#include "../signals/SignallingValue.h"
#include "IShapeAppModel.h"

class IShapesAppModel
{
public:
	using AddShapeSignal = Signal<void(IShapeAppModelPtr shape, size_t position)>;
	using RemoveShapeSignal = Signal<void(std::string const& id)>;
	using AddShapeSlot = AddShapeSignal::slot_type;
	using RemoveShapeSlot = RemoveShapeSignal::slot_type;

	virtual void AddShape(std::string const& shapeType) = 0;
	virtual void RemoveShape(std::string const& id) = 0;
	virtual ScopedConnection DoOnAddShape(const AddShapeSlot& slot) = 0;
	virtual ScopedConnection DoOnRemoveShape(const RemoveShapeSlot& slot) = 0;

	[[nodiscard]] virtual IShapeAppModelPtr GetShape(std::string const& id) const = 0;
	virtual IShapeAppModelPtr GetShape(std::string const& id) = 0;
	[[nodiscard]] virtual IShapeAppModelPtr GetShape(size_t position) const = 0;
	virtual IShapeAppModelPtr GetShape(size_t position) = 0;
	virtual void ForEach(std::function<bool(IShapeAppModelPtr)> callback) const = 0;
	[[nodiscard]] virtual size_t GetSize() const = 0;

	virtual void Undo() = 0;
	virtual void Redo() = 0;
	[[nodiscard]] virtual bool CanUndo() const = 0;
	[[nodiscard]] virtual bool CanRedo() const = 0;

	virtual ~IShapesAppModel() = default;
};