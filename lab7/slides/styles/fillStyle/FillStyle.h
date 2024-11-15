#pragma once
#include "IFillStyle.h"

class FillStyle final : public IFillStyle
{
public:
	explicit FillStyle(Color const color)
		: m_color(color)
	{
	}

	[[nodiscard]] std::optional<bool> isEnabled() const override
	{
		return m_enabled;
	}

	void setEnabled(bool const enabled) override
	{
		m_enabled = enabled;
	}

	[[nodiscard]] std::optional<Color> GetColor() const override
	{
		return m_color;
	}

	void SetColor(Color const color) override
	{
		m_color = color;
	}

private:
	bool m_enabled = true;
	Color m_color = 0;
};
