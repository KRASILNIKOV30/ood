#include "ShapesViewModel.h"
#include "ShapeViewModel.h"
#include <cmath>

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

void ShapesViewModel::RemoveSelectedShapes()
{
	for (const auto& id : m_selectedIds)
	{
		m_shapesAppModel->RemoveShape(id);
	}
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
	return m_selectionChangeSignal.connect(slot);
}
ScopedConnection ShapesViewModel::DoOnUpdate(UpdateSlot const& slot)
{
	return m_updateSignal.connect(slot);
}
void ShapesViewModel::ReframeSelected(const Frame& frame)
{
	const auto& shapes = GetSelectedShapes();
	const auto frameOpt = GetSelectedFrame();
	if (!frameOpt.has_value())
	{
		return;
	}
	const auto [position, size] = frameOpt.value();
	const auto [width, height] = size;

	const double scaleX = static_cast<double>(frame.size.width) / width;
	const double scaleY = static_cast<double>(frame.size.height) / height;

	for (const auto& shape : shapes)
	{
		Frame shapeFrame = shape->GetFrame();

		const double newLeftTopX = frame.position.x + (shapeFrame.position.x - position.x) * scaleX;
		const double newLeftTopY = frame.position.y + (shapeFrame.position.y - position.y) * scaleY;

		const double newWidth = shapeFrame.size.width * scaleX;
		const double newHeight = shapeFrame.size.height * scaleY;

		shape->Reframe({ { static_cast<int>(std::round(newLeftTopX)), static_cast<int>(std::round(newLeftTopY)) },
			{ static_cast<int>(std::round(newWidth)), static_cast<int>(std::round(newHeight)) } });
	}
}

std::vector<IShapeViewModelPtr> ShapesViewModel::GetSelectedShapes() const
{
	const auto ids = GetSelectedShapeId();
	std::vector<IShapeViewModelPtr> shapes;
	for (const auto& id : ids)
	{
		const auto shape = m_shapes.Find(id);
		if (shape.has_value())
		{
			shapes.emplace_back(shape.value());
		}
	}
	return shapes;
}

void ShapesViewModel::ApplyReframeSelected(const Frame& frame)
{
	const auto& shapes = GetSelectedShapes();
	const auto frameOpt = GetSelectedFrame();
	if (!frameOpt.has_value())
	{
		return;
	}
	const auto [position, size] = frameOpt.value();
	const auto [width, height] = size;

	const double scaleX = static_cast<double>(frame.size.width) / width;
	const double scaleY = static_cast<double>(frame.size.height) / height;

	for (const auto& shape : shapes)
	{
		Frame shapeFrame = shape->GetFrame();

		const int newLeftTopX = frame.position.x + (shapeFrame.position.x - position.x) * scaleX;
		const int newLeftTopY = frame.position.y + (shapeFrame.position.y - position.y) * scaleY;
		const int newWidth = shapeFrame.size.width * scaleX;
		const int newHeight = shapeFrame.size.height * scaleY;

		shape->ApplyReframe({ { newLeftTopX, newLeftTopY }, { newWidth, newHeight } });
	}
}
void ShapesViewModel::ResetSelection()
{
	m_selectedIds.clear();
	m_selectionChangeSignal();
}

std::optional<Frame> ShapesViewModel::GetSelectedFrame() const
{
	const auto& shapes = GetSelectedShapes();
	if (shapes.empty())
	{
		return std::nullopt;
	}

	const auto [position, size] = shapes.front()->GetFrame();
	const auto [x, y] = position;
	const auto [width, height] = size;

	auto minY = y;
	auto minX = x;
	auto maxX = x + width;
	auto maxY = y + height;

	for (auto const& shape : shapes)
	{
		const auto [position, size] = shape->GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		minY = std::min(minY, y);
		minX = std::min(minX, x);
		maxY = std::max(maxY, y + height);
		maxX = std::max(maxX, x + width);
	}

	return Frame{ { minX, minY }, maxX - minX, maxY - minY };
}

void ShapesViewModel::ReselectShape(std::string const& id)
{
	m_selectedIds = Ids{ id };
	m_selectionChangeSignal();
}

void ShapesViewModel::SelectShape(std::string const& id)
{
	m_selectedIds.push_back(id);
	m_selectionChangeSignal();
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
Ids ShapesViewModel::GetSelectedShapeId() const
{
	return m_selectedIds;
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
	m_onShapeClickConnections.push_back(shapeViewModel->DoOnClick([id, this](bool ctrl) {
		if (ctrl)
		{
			SelectShape(id);
		}
		else
		{
			ReselectShape(id);
		}
	}));
	m_reframeShapeConnections.push_back(shapeViewModel->DoOnReframe([&](const auto& frame) {
		m_updateSignal();
	}));
	SelectShape(id);
	m_addShapeSignal(shapeViewModel, position);
}

void ShapesViewModel::DoRemoveShape(std::string const& id)
{
	m_shapes.Remove(id);
	m_removeShapeSignal(id);
}
