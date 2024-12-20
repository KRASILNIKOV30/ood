#pragma once
#include "../../../../lab5_cmake/history/AbstractUndoableEdit.h"
#include "../../model/IShapes.h"

class AddShapeEdit final : public undo::AbstractUndoableEdit
{
public:
	AddShapeEdit(std::string shapeType, IShapes* shapes)
		: m_shapeType(std::move(shapeType))
		, m_shapes(shapes)
	{
	}

private:
	void UndoImpl() override
	{
		m_shapes->RemoveLastShape();
	}

	void RedoImpl() override
	{
		m_shapes->AddShape(m_shapeType);
	}

private:
	std::string m_shapeType;
	IShapes* m_shapes;
};