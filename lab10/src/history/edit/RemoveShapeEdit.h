#pragma once
#include <utility>

#include "../../../../lab5_cmake/history/AbstractUndoableEdit.h"
#include "../../model/IShapes.h"

class RemoveShapeEdit final : public undo::AbstractUndoableEdit
{
public:
	RemoveShapeEdit(IShapePtr shape, const size_t position, IShapes* shapes)
		: m_shape(std::move(shape))
		, m_position(position)
		, m_shapes(shapes)
	{
	}

private:
	void UndoImpl() override
	{
		m_shapes->AddShape(m_shape, m_position);
	}

	void RedoImpl() override
	{
		m_shapes->RemoveShape(m_shape->GetId());
	}

private:
	IShapePtr m_shape;
	size_t m_position;
	IShapes* m_shapes;
};