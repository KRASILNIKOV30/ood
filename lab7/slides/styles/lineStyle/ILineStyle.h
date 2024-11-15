#pragma once
#include "../../Color.h"

class ILineStyle
{
public:
	[[nodiscard]] virtual bool isEnabled() const = 0;
	virtual void setEnabled(bool enabled) = 0;
	[[nodiscard]] virtual Color GetColor() const = 0;
	virtual void SetColor(Color color) = 0;
	[[nodiscard]] virtual double GetLineWidth() const = 0;
	virtual void SetLineWidth(int width) = 0;
	virtual ~ILineStyle() = 0;
};