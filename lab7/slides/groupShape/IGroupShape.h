#pragma once
#include "../shapes/IShape.h"

class IGroupShape : public IShape
{
public:
	[[nodiscard]] virtual size_t GetShapesCount() const = 0;
	virtual IShapePtr GetShape(size_t index) = 0;
	virtual void AddShape(IShapePtr const& shape) = 0;
};