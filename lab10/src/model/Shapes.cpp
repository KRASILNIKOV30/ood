#include "Shapes.h"

std::string Shapes::AddShape(const std::string& type)
{
	const auto shape = m_factory.CreateShape(type);
	const auto id = shape->GetId();
	AddShape(shape);
	return id;
}

void Shapes::AddShape(IShapePtr const& shape, const std::optional<size_t> position)
{
	const auto pos = position.value_or(GetSize());
	m_shapes.Insert(shape, pos);
	m_addShapeSignal(shape, pos);
}

size_t Shapes::RemoveShape(std::string const& id)
{
	const auto position = m_shapes.Remove(id);
	if (!position.has_value())
	{
		throw std::invalid_argument("shape does not exist");
	}
	m_removeShapeSignal(id);
	return position.value();
}
size_t Shapes::RemoveLastShape()
{
	return RemoveShape(m_shapes.Get(m_shapes.GetSize() - 1)->GetId());
}

IShapePtr Shapes::GetShape(std::string const& id) const
{
	auto const shape = m_shapes.Find(id);
	if (!shape.has_value())
	{
		return nullptr;
	}
	return shape.value();
}

IShapePtr Shapes::GetShape(const std::string& id)
{
	return const_cast<const Shapes*>(this)->GetShape(id);
}

void Shapes::ForEach(const std::function<bool(IShapePtr)> callback) const
{
	m_shapes.ForEach(callback);
}

ScopedConnection Shapes::DoOnAddShape(const AddShapeSlot& slot)
{
	return m_addShapeSignal.connect(slot);
}

ScopedConnection Shapes::DoOnRemoveShape(const RemoveShapeSlot& slot)
{
	return m_removeShapeSignal.connect(slot);
}

size_t Shapes::GetSize() const
{
	return m_shapes.GetSize();
}