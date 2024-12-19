#pragma once
#include "../model/IShape.h"
#include "../signals/SignallingValue.h"
#include "IShapeAppModel.h"

class IShapesAppModel
{
public:
	using AddShapeSignal = Signal<void(IShapeAppModel* shape, size_t position)>;
	using RemoveShapeSignal = Signal<void(std::string const& id)>;
	using AddShapeSlot = AddShapeSignal::slot_type;
	using RemoveShapeSlot = RemoveShapeSignal::slot_type;

	virtual void AddShape(std::string const& shapeType) = 0;
	virtual void RemoveShape(std::string const& id) = 0;
	virtual ScopedConnection DoOnAddShape(AddShapeSlot& slot) = 0;
	virtual ScopedConnection DoOnRemoveShape(RemoveShapeSlot& slot) = 0;

	[[nodiscard]] virtual const IShapeAppModel* GetShape(std::string const& id) const = 0;
	virtual IShapeAppModel* GetShape(std::string const& id) = 0;
	virtual void ForEach(std::function<bool(const IShapeAppModel*)> callback) const = 0;

	virtual void Undo() const = 0;
	virtual void Redo() const = 0;

	virtual ~IShapesAppModel() = 0;
};