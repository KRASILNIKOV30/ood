#pragma once
#include "../../Color.h"
#include <optional>

class IFillStyle
{
public:
	[[nodiscard]] virtual std::optional<bool> isEnabled() const = 0;
	virtual void setEnabled(bool enabled) = 0;
	[[nodiscard]] virtual std::optional<Color> GetColor() const = 0;
	virtual void SetColor(Color color) = 0;
	virtual ~IFillStyle() = 0;
};