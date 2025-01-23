#pragma once
#include "../signals/SignallingValue.h"
#include "IShapeViewModel.h"
#include <optional>

class IShapesViewModel
{
public:
	using AddShapeSignal = Signal<void(IShapeViewModelPtr shape, size_t position)>;
	using RemoveShapeSignal = Signal<void(std::string const& id)>;
	using AddShapeSlot = AddShapeSignal::slot_type;
	using RemoveShapeSlot = RemoveShapeSignal::slot_type;
	using SelectionChangeSignal = Signal<void(std::optional<std::string> const& id)>;
	using SelectionChangeSlot = SelectionChangeSignal::slot_type;

	virtual void AddShape(std::string const& shapeType) = 0;
	virtual void RemoveShape() = 0;
	virtual void OnCanvasClick() = 0;
	virtual ScopedConnection DoOnAddShape(const AddShapeSlot& slot) = 0;
	virtual ScopedConnection DoOnRemoveShape(const RemoveShapeSlot& slot) = 0;
	virtual ScopedConnection DoOnSelectionChange(const SelectionChangeSlot& slot) = 0;

	[[nodiscard]] virtual IShapeViewModelPtr GetShape(std::string const& id) const = 0;
	virtual IShapeViewModelPtr GetShape(std::string const& id) = 0;
	[[nodiscard]] virtual IShapeViewModelPtr GetShape(size_t position) const = 0;
	virtual IShapeViewModelPtr GetShape(size_t position) = 0;
	virtual void ForEach(std::function<bool(IShapeViewModelPtr)> callback) const = 0;
	[[nodiscard]] virtual size_t GetSize() const = 0;
	[[nodiscard]] virtual std::optional<std::string> GetSelectedShapeId() const = 0;

	virtual void Undo() = 0;
	virtual void Redo() = 0;
	[[nodiscard]] virtual bool CanUndo() const = 0;
	[[nodiscard]] virtual bool CanRedo() const = 0;

	virtual ~IShapesViewModel() = default;
};

using IShapesViewModelPtr = std::shared_ptr<IShapesViewModel>;
