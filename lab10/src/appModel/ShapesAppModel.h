#pragma once
#include "../../../lab5_cmake/history/UndoManager.h"
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
	ScopedConnection DoOnAddShape(AddShapeSlot& slot) override;
	ScopedConnection DoOnRemoveShape(RemoveShapeSlot& slot) override;

	[[nodiscard]] const IShapeAppModel* GetShape(const std::string& id) const override;
	IShapeAppModel* GetShape(const std::string& id) override;
	[[nodiscard]] const IShapeAppModel* GetShape(size_t position) const override;
	IShapeAppModel* GetShape(size_t position) override;
	void ForEach(std::function<bool(const IShapeAppModel*)> callback) const override;

	void Undo() const override;
	void Redo() const override;

	~ShapesAppModel() override = default;

private:
	void AddShape(IShape* shape, size_t position);

private:
	Repository<IShapeAppModel> m_shapes;
	undo::UndoManager m_history;
	IShapes* m_shapesDomainModel;
	AddShapeSignal m_addShapeSignal;
	RemoveShapeSignal m_removeShapeSignal;
	ScopedConnection m_addShapeSignalConnection;
	ScopedConnection m_removeShapeSignalConnection;
};
