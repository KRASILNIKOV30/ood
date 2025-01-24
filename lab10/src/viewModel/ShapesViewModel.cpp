#include "ShapesViewModel.h"

#include "ShapeViewModel.h"
#include <utility>

ShapesViewModel::ShapesViewModel(IShapesAppModelPtr const& shapesAppModel)
	: m_shapesAppModel(shapesAppModel)
{
	m_addShapeSignalConnection = m_shapesAppModel->DoOnAddShape([&](const auto& shape, const auto pos) {
		DoAddShape(shape, pos);
	});
	m_removeShapeSignalConnection = m_shapesAppModel->DoOnRemoveShape([&](const auto& id) {
		DoRemoveShape(id);
	});
}

void ShapesViewModel::AddShape(const std::string& shapeType)
{
	m_shapesAppModel->AddShape(shapeType);
}

void ShapesViewModel::RemoveShape()
{
	if (m_selectedId.GetValue().has_value())
	{
		m_shapesAppModel->RemoveShape(m_selectedId.GetValue().value());
	}
}

void ShapesViewModel::OnCanvasClick()
{
	m_selectedId = std::nullopt;
}

ScopedConnection ShapesViewModel::DoOnAddShape(const AddShapeSlot& slot)
{
	return m_addShapeSignal.connect(slot);
}

ScopedConnection ShapesViewModel::DoOnRemoveShape(const RemoveShapeSlot& slot)
{
	return m_removeShapeSignal.connect(slot);
}

ScopedConnection ShapesViewModel::DoOnSelectionChange(const SelectionChangeSlot& slot)
{
	return m_selectedId.Connect1(slot, false);
}
ScopedConnection ShapesViewModel::DoOnUpdate(UpdateSlot const& slot)
{
	return m_updateSignal.connect(slot);
}
void ShapesViewModel::ReframeSelected(const Frame& frame)
{
	const auto shape = GetSelectedShape();
	if (!shape.has_value())
	{
		return;
	}
	shape.value()->Reframe(frame);
}

std::optional<IShapeViewModelPtr> ShapesViewModel::GetSelectedShape() const
{
	const auto idOpt = GetSelectedShapeId();
	if (!idOpt.has_value())
	{
		return std::nullopt;
	}
	const auto& id = idOpt.value();
	const auto shape = m_shapes.Find(id);
	if (!shape.has_value())
	{
		return std::nullopt;
	}
	return shape;
}

void ShapesViewModel::ApplyReframeSelected(const Frame& frame)
{
	const auto shape = GetSelectedShape();
	if (!shape.has_value())
	{
		return;
	}
	shape.value()->ApplyReframe(frame);
}
void ShapesViewModel::ResetSelection()
{
	m_selectedId = std::nullopt;
}

IShapeViewModelPtr ShapesViewModel::GetShape(const std::string& id) const
{
	return m_shapes.Get(id);
}

IShapeViewModelPtr ShapesViewModel::GetShape(const std::string& id)
{
	return m_shapes.Get(id);
}

IShapeViewModelPtr ShapesViewModel::GetShape(size_t position) const
{
	return m_shapes.Get(position);
}

IShapeViewModelPtr ShapesViewModel::GetShape(size_t position)
{
	return m_shapes.Get(position);
}

void ShapesViewModel::ForEach(const std::function<bool(IShapeViewModelPtr)> callback) const
{
	m_shapes.ForEach(callback);
}

size_t ShapesViewModel::GetSize() const
{
	return m_shapes.GetSize();
}
std::optional<std::string> ShapesViewModel::GetSelectedShapeId() const
{
	return m_selectedId.GetValue();
}

void ShapesViewModel::Undo()
{
	m_shapesAppModel->Undo();
}

void ShapesViewModel::Redo()
{
	m_shapesAppModel->Redo();
}

bool ShapesViewModel::CanUndo() const
{
	return m_shapesAppModel->CanUndo();
}

bool ShapesViewModel::CanRedo() const
{
	return m_shapesAppModel->CanRedo();
}

void ShapesViewModel::DoAddShape(IShapeAppModelPtr const& shape, size_t position)
{
	const auto shapeViewModel = std::make_shared<ShapeViewModel>(shape);
	m_shapes.Insert(shapeViewModel, position);
	const auto id = shapeViewModel->GetId();
	m_onShapeClickConnections.push_back(shapeViewModel->DoOnClick([id, this] {
		m_selectedId = id;
	}));
	m_reframeShapeConnections.push_back(shapeViewModel->DoOnReframe([&](const auto& frame) {
		m_updateSignal();
	}));
	m_selectedId = id;
	m_addShapeSignal(shapeViewModel, position);
}

void ShapesViewModel::DoRemoveShape(std::string const& id)
{
	m_shapes.Remove(id);
	m_removeShapeSignal(id);
}
