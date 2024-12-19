#pragma once
#include "../Frame.h"
#include <memory>
#include <string>

class IShapeAppModel
{
public:
	[[nodiscard]] virtual std::string GetId() const = 0;
	[[nodiscard]] virtual Frame GetFrame() const = 0;
	[[nodiscard]] virtual std::string GetType() const = 0;

	virtual ~IShapeAppModel() = default;
};

using IShapeAppModelPtr = std::unique_ptr<IShapeAppModel>;
