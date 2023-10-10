#pragma once
#include <memory>
#include <vector>
#include "CShape.h"

using Shapes = std::vector<std::shared_ptr<CShape>>;

class CPictureDraft
{
public:
	explicit CPictureDraft(Shapes&& shapes)
		: m_shapes(std::move(shapes))
	{
	}

	std::shared_ptr<CShape> GetShape(const int index)
	{
		return m_shapes[index];
	}

	size_t GetShapeCount() const
	{
		return m_shapes.size();
	}

private:
	Shapes m_shapes;
};
