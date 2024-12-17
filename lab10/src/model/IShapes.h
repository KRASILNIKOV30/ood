#pragma once
#include "Shape.h"

#include <functional>

class IShapes
{
public:
	virtual void AddShape(IShapePtr&& shape, std::optional<size_t> position) = 0;
	virtual size_t RemoveShape(std::string const& id) = 0;
	[[nodiscard]] virtual const IShape* GetShape(std::string const& id) const = 0;
	[[nodiscard]] virtual size_t GetSize() const = 0;
	virtual void ForEach(std::function<bool(const IShape*)> callback) const = 0;

	virtual ~IShapes() = default;
};