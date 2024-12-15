#pragma once
#include "../Frame.h"

#include <memory>
#include <string>

class IShape
{
public:
	[[nodiscard]] virtual Frame GetFrame() const = 0;
	[[nodiscard]] virtual std::string GetType() const = 0;
	[[nodiscard]] virtual std::string GetId() const = 0;

	virtual ~IShape() = default;
};

using IShapePtr = std::unique_ptr<IShape>;