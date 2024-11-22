#pragma once
#include "../../Color.h"
#include <optional>

class IFillStyle
{
public:
	[[nodiscard]] virtual std::optional<bool> IsEnabled() const = 0;
	virtual void SetEnabled(bool enabled) = 0;
	[[nodiscard]] virtual std::optional<Color> GetColor() const = 0;
	virtual void SetColor(Color color) = 0;
	virtual ~IFillStyle() = 0;
};

using IFillStylePtr = std::shared_ptr<IFillStyle>;
