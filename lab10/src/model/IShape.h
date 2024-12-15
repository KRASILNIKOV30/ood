#pragma once
#include "../Frame.h"

#include <string>

class IShape
{
public:
	[[nodiscard]] virtual Frame GetFrame() const = 0;
	[[nodiscard]] virtual std::string GetType() const = 0;

	virtual ~IShape() = default;
};