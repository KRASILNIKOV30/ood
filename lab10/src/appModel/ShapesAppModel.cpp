#include "./ShapesAppModel.h"
#include "../history/edit/AddShapeEdit.h"
#include "../history/edit/RemoveShapeEdit.h"
#include "./ShapeAppModel.h"

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
	m_history.AddEdit(std::make_unique<AddShapeEdit>(shapeType, m_shapesDomainModel));
}

void ShapesAppModel::RemoveShape(const std::string& id)
{
	IShapePtr shape(m_shapesDomainModel->GetShape(id));
	const size_t pos = m_shapesDomainModel->RemoveShape(id);
	m_history.AddEdit(std::make_unique<RemoveShapeEdit>(shape, pos, m_shapesDomainModel));
}

ScopedConnection ShapesAppModel::DoOnAddShape(const AddShapeSlot& slot)
{
	return m_addShapeSignal.connect(slot);
}

ScopedConnection ShapesAppModel::DoOnRemoveShape(const RemoveShapeSlot& slot)
{
	return m_removeShapeSignal.connect(slot);
}

IShapeAppModelPtr ShapesAppModel::GetShape(const std::string& id) const
{
	return m_shapes.Get(id);
}

IShapeAppModelPtr ShapesAppModel::GetShape(const std::string& id)
{
	return m_shapes.Get(id);
}

IShapeAppModelPtr ShapesAppModel::GetShape(const size_t position) const
{
	return m_shapes.Get(position);
}

IShapeAppModelPtr ShapesAppModel::GetShape(const size_t position)
{
	return m_shapes.Get(position);
}

void ShapesAppModel::ForEach(std::function<bool(IShapeAppModelPtr)> callback) const
{
	m_shapes.ForEach(callback);
}
size_t ShapesAppModel::GetSize() const
{
	return m_shapes.GetSize();
}

void ShapesAppModel::Undo()
{
	if (CanUndo())
	{
		m_history.Undo();
	}
}

void ShapesAppModel::Redo()
{
	if (CanRedo())
	{
		m_history.Redo();
	}
}

bool ShapesAppModel::CanUndo() const
{
	return m_history.CanUndo();
}

bool ShapesAppModel::CanRedo() const
{
	return m_history.CanRedo();
}

void ShapesAppModel::DoAddShape(IShapePtr const& shape, const size_t position)
{
	const auto appShape = std::make_shared<ShapeAppModel>(shape, [&](const auto& edit) { m_history.AddEdit(edit); });
	m_shapes.Insert(appShape, position);
	m_addShapeSignal(appShape, position);
}

void ShapesAppModel::DoRemoveShape(std::string const& id)
{
	m_shapes.Remove(id);
	m_removeShapeSignal(id);
}