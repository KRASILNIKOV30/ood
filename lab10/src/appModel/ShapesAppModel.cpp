#include "ShapesAppModel.h"

#include "ShapeAppModel.h"

ShapesAppModel::ShapesAppModel(IShapes* shapes)
	: m_shapesDomainModel(shapes)
{
	m_addShapeSignalConnection = m_shapesDomainModel->DoOnAddShape([&](auto shape, auto pos) {
		DoAddShape(shape, pos);
	});
	m_removeShapeSignalConnection = m_shapesDomainModel->DoOnRemoveShape([&](const auto& id) {
		DoRemoveShape(id);
	});
}

void ShapesAppModel::AddShape(const std::string& shapeType)
{
	m_shapesDomainModel->AddShape(shapeType);
}

void ShapesAppModel::RemoveShape(const std::string& id)
{
	m_shapesDomainModel->RemoveShape(id);
}

ScopedConnection ShapesAppModel::DoOnAddShape(AddShapeSlot& slot)
{
	return {};
}

ScopedConnection ShapesAppModel::DoOnRemoveShape(RemoveShapeSlot& slot)
{
	return {};
}

const IShapeAppModel* ShapesAppModel::GetShape(const std::string& id) const
{
	return m_shapes.Get(id);
}

IShapeAppModel* ShapesAppModel::GetShape(const std::string& id)
{
	return m_shapes.Get(id);
}

const IShapeAppModel* ShapesAppModel::GetShape(size_t position) const
{
	return nullptr;
}

IShapeAppModel* ShapesAppModel::GetShape(size_t position)
{
	return m_shapes.Get(position);
}

void ShapesAppModel::ForEach(std::function<bool(const IShapeAppModel*)> callback) const
{
	m_shapes.ForEach(callback);
}

void ShapesAppModel::Undo() const
{
}

void ShapesAppModel::Redo() const
{
}

void ShapesAppModel::DoAddShape(IShape* shape, const size_t position)
{
	std::unique_ptr<IShapeAppModel> appShape = std::make_unique<ShapeAppModel>(shape);
	m_addShapeSignal(appShape.get(), position);
	m_shapes.Insert(std::move(appShape));
}

void ShapesAppModel::DoRemoveShape(std::string const& id)
{
	m_shapes.Remove(id);
	m_removeShapeSignal(id);
}