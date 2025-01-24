#pragma once
#include "../history/UndoManager.h"
#include "../model/IShapes.h"
#include "../repository/Repository.h"
#include "IShapeAppModel.h"
#include "IShapesAppModel.h"

class ShapesAppModel final : public IShapesAppModel
{
public:
	ShapesAppModel(IShapes* shapes);

	void AddShape(const std::string& shapeType) override;
	void RemoveShape(const std::string& id) override;
	ScopedConnection DoOnAddShape(const AddShapeSlot& slot) override;
	ScopedConnection DoOnRemoveShape(const RemoveShapeSlot& slot) override;

	[[nodiscard]] IShapeAppModelPtr GetShape(const std::string& id) const override;
	IShapeAppModelPtr GetShape(const std::string& id) override;
	[[nodiscard]] IShapeAppModelPtr GetShape(size_t position) const override;
	IShapeAppModelPtr GetShape(size_t position) override;
	void ForEach(std::function<bool(IShapeAppModelPtr)> callback) const override;
	[[nodiscard]] size_t GetSize() const override;

	void Undo() override;
	void Redo() override;
	[[nodiscard]] bool CanUndo() const override;
	[[nodiscard]] bool CanRedo() const override;

	ShapesAppModel(const ShapesAppModel&) = delete;
	ShapesAppModel& operator=(const ShapesAppModel&) = delete;

private:
	void DoAddShape(IShapePtr const& shape, size_t position);
	void DoRemoveShape(std::string const& id);

private:
	Repository<IShapeAppModel> m_shapes;
	UndoManager m_history;
	IShapes* m_shapesDomainModel;
	AddShapeSignal m_addShapeSignal;
	RemoveShapeSignal m_removeShapeSignal;
	ScopedConnection m_addShapeSignalConnection;
	ScopedConnection m_removeShapeSignalConnection;
};
