#include "Shapes.h"

void Shapes::AddShape(IShapePtr&& shape)
{
	const auto id = shape->GetId();
	m_shapes.push_back(std::move(shape));

	const auto inserted = m_shapesMap.emplace(id, --m_shapes.end()).second;
	if (!inserted)
	{
		m_shapes.pop_back();
	}
}
void Shapes::RemoveShape(std::string const& id)
{
	auto mapIt = m_shapesMap.find(id);
	if (mapIt == m_shapesMap.end())
	{
		return;
	}

	m_shapes.erase(mapIt->second);
	m_shapesMap.erase(mapIt);
}

const IShape* Shapes::GetShape(std::string const& id) const
{
	const auto mapIt = m_shapesMap.find(id);
	if (mapIt == m_shapesMap.end())
	{
		return nullptr;
	}

	return mapIt->second->get();
}

void Shapes::ForEach(const std::function<bool(const IShape*)> callback) const
{
	for (const auto& shape : m_shapes)
	{
		if (!callback(shape.get()))
		{
			return;
		}
	}
}