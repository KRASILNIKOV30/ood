#pragma once
#include "../../Color.h"

class IFillStyle
{
public:
	[[nodiscard]] virtual bool isEnabled() const = 0;
	virtual void setEnabled(bool enabled) = 0;
	[[nodiscard]] virtual Color GetColor() const = 0;
	virtual void SetColor(Color color) = 0;
	virtual ~IFillStyle() = 0;
};
