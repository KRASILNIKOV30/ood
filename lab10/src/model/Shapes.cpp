#include "Shapes.h"

void Shapes::AddShape(IShapePtr&& shape, const std::optional<size_t> position)
{
	const auto pos = position.has_value()
		? position.value()
		: GetSize();
	m_shapes.Insert(shape->GetId(), std::move(shape), pos);
}

size_t Shapes::RemoveShape(std::string const& id)
{
	const auto position = m_shapes.Remove(id);
	if (!position.has_value())
	{
		throw std::invalid_argument("shape does not exist");
	}
	return position.value();
}

const IShape* Shapes::GetShape(std::string const& id) const
{
	auto const shape = m_shapes.Find(id);
	if (!shape.has_value())
	{
		return nullptr;
	}
	return shape.value();
}

IShape* Shapes::GetShape(const std::string& id)
{
	return const_cast<IShape*>(const_cast<const Shapes*>(this)->GetShape(id));
}

void Shapes::ForEach(const std::function<bool(const IShape*)> callback) const
{
	m_shapes.ForEach(callback);
}

ScopedConnection Shapes::DoOnAddShape(const AddShapeSlot& slot)
{
	return {};
}

ScopedConnection Shapes::DoOnRemoveShape(const RemoveShapeSlot& slot)
{
	return {};
}

size_t Shapes::GetSize() const
{
	return m_shapes.GetSize();
}