#pragma once
#include "../../Color.h"
#include <optional>

class ILineStyle
{
public:
	[[nodiscard]] virtual std::optional<bool> isEnabled() const = 0;
	virtual void SetEnabled(bool enabled) = 0;
	[[nodiscard]] virtual std::optional<Color> GetColor() const = 0;
	virtual void SetColor(Color color) = 0;
	[[nodiscard]] virtual std::optional<double> GetLineWidth() const = 0;
	virtual void SetLineWidth(double width) = 0;
	virtual ~ILineStyle() = default;
};

using ILineStylePtr = std::shared_ptr<ILineStyle>;