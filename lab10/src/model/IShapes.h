#pragma once
#include "Shape.h"

#include <functional>

class IShapes
{
public:
	virtual void AddShape(IShapePtr&& shape) = 0;
	virtual void RemoveShape(std::string const& id) = 0;
	[[nodiscard]] virtual const IShape* GetShape(std::string const& id) const = 0;
	virtual void ForEach(std::function<bool(const IShape*)> callback) const = 0;

	virtual ~IShapes() = default;
};