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
	using SelectionChangeSignal = Signal<void()>;
	using SelectionChangeSlot = SelectionChangeSignal::slot_type;
	using UpdateSignal = EmptySignal;
	using UpdateSlot = UpdateSignal::slot_type;

	virtual void AddShape(std::string const& shapeType) = 0;
	virtual void RemoveSelectedShapes() = 0;
	virtual ScopedConnection DoOnAddShape(const AddShapeSlot& slot) = 0;
	virtual ScopedConnection DoOnRemoveShape(const RemoveShapeSlot& slot) = 0;
	virtual ScopedConnection DoOnSelectionChange(const SelectionChangeSlot& slot) = 0;
	virtual ScopedConnection DoOnUpdate(const UpdateSlot&) = 0;

	[[nodiscard]] virtual IShapeViewModelPtr GetShape(std::string const& id) const = 0;
	virtual IShapeViewModelPtr GetShape(std::string const& id) = 0;
	[[nodiscard]] virtual IShapeViewModelPtr GetShape(size_t position) const = 0;
	virtual IShapeViewModelPtr GetShape(size_t position) = 0;
	virtual void ForEach(std::function<bool(IShapeViewModelPtr)> callback) const = 0;
	[[nodiscard]] virtual size_t GetSize() const = 0;
	[[nodiscard]] virtual std::vector<std::string> GetSelectedShapeId() const = 0;
	virtual void ReframeSelected(Frame const& frame) = 0;
	virtual void ApplyReframeSelected(Frame const& frame) = 0;
	virtual void ResetSelection() = 0;
	[[nodiscard]] virtual std::optional<Frame> GetSelectedFrame() const = 0;

	virtual void Undo() = 0;
	virtual void Redo() = 0;
	[[nodiscard]] virtual bool CanUndo() const = 0;
	[[nodiscard]] virtual bool CanRedo() const = 0;

	virtual ~IShapesViewModel() = default;
};

using IShapesViewModelPtr = std::shared_ptr<IShapesViewModel>;
