#include "ShapesAppModel.h"

#include "ShapeAppModel.h"

ShapesAppModel::ShapesAppModel(IShapes* shapes)
	: m_shapesDomainModel(shapes)
{
	m_addShapeSignalConnection = m_shapesDomainModel->DoOnAddShape([&](auto shape, auto pos) {
		AddShape(shape, pos);
	});
}

void ShapesAppModel::AddShape(const std::string& shapeType)
{
	m_shapesDomainModel->AddShape(shapeType);
}

void ShapesAppModel::RemoveShape(const std::string& id)
{
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
	return nullptr;
}

IShapeAppModel* ShapesAppModel::GetShape(const std::string& id)
{
	return nullptr;
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
}

void ShapesAppModel::Undo() const
{
}

void ShapesAppModel::Redo() const
{
}

void ShapesAppModel::AddShape(IShape* shape, const size_t position)
{
	std::unique_ptr<IShapeAppModel> appShape = std::make_unique<ShapeAppModel>(shape);
	m_addShapeSignal(appShape.get(), position);
	m_shapes.Insert(std::move(appShape));
}