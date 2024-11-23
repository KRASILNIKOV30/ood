#pragma once
#include <utility>
#include "ILineStyle.h"
#include "../StyleEnumerators.h"

class CompositeLineStyle final : public ILineStyle
{
public:
	explicit CompositeLineStyle(LineStyleEnumerator enumerator)
		: m_enumerator(std::move(enumerator))
	{}

	[[nodiscard]] std::optional<bool> isEnabled() const override
	{
		std::optional<bool> enabled = std::nullopt;
		m_enumerator([&](const auto& lineStyle) {
			if (!enabled)
			{
				enabled = lineStyle->isEnabled();
			}
			if (enabled != lineStyle->isEnabled())
			{
				enabled = std::nullopt;
				return false;
			}
			return true;
		});

		return enabled;
	}

	void SetEnabled(bool const enabled) override
	{
		m_enumerator([&](const auto& lineStyle) {
			lineStyle->SetEnabled(enabled);
			return true;
		});
	}

	[[nodiscard]] std::optional<Color> GetColor() const override
	{
		std::optional<Color> color = std::nullopt;
		m_enumerator([&](const auto& lineStyle) {
			if (!color)
			{
				color = lineStyle->GetColor();
			}
			if (color != lineStyle->GetColor())
			{
				color = std::nullopt;
				return false;
			}
			return true;
		});

		return color;
	}

	void SetColor(Color const color) override
	{
		m_enumerator([&](const auto& lineStyle) {
			lineStyle->SetColor(color);
			return true;
		});
	}

	[[nodiscard]] std::optional<double> GetLineWidth() const override
	{
		std::optional<double> lineWidth = std::nullopt;
		m_enumerator([&](const auto& lineStyle) {
			if (!lineWidth)
			{
				lineWidth = lineStyle->GetLineWidth();
			}
			if (lineWidth != lineStyle->GetLineWidth())
			{
				lineWidth = std::nullopt;
				return false;
			}
			return true;
		});

		return lineWidth;
	}

	void SetLineWidth(double const width) override
	{
		m_enumerator([&](const auto& lineStyle) {
			lineStyle->SetLineWidth(width);
			return true;
		});
	}

private:
	LineStyleEnumerator m_enumerator;
};