#pragma once
#include "ILineStyle.h"

class LineStyle final : public ILineStyle
{
public:
	explicit LineStyle(const Color color, const double lineWidth = 1)
		: m_color(color)
		, m_lineWidth(lineWidth)
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

	void SetLineWidth(int const width) override
	{
		m_lineWidth = width;
	}

	[[nodiscard]] std::optional<double> GetLineWidth() const override
	{
		return m_lineWidth;
	}

private:
	bool m_enabled = true;
	Color m_color = 0;
	double m_lineWidth = 1;
};
