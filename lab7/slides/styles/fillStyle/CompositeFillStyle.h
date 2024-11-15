#pragma once
#include <utility>
#include "IFillStyle.h"
#include "../StyleEnumerators.h"

class CompositeFillStyle final : public IFillStyle
{
public:
	explicit CompositeFillStyle(FillStyleEnumerator enumerator)
		: m_enumerator(std::move(enumerator))
	{}

	[[nodiscard]] std::optional<bool> IsEnabled() const override
	{
		std::optional<bool> enabled = std::nullopt;
		m_enumerator([&](const IFillStyle* FillStyle) {
			if (!enabled)
			{
				enabled = FillStyle->IsEnabled();
			}
			if (enabled != FillStyle->IsEnabled())
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
		m_enumerator([&](IFillStyle* FillStyle) {
			FillStyle->SetEnabled(enabled);
			return true;
		});
	}

	[[nodiscard]] std::optional<Color> GetColor() const override
	{
		std::optional<Color> color = std::nullopt;
		m_enumerator([&](const IFillStyle* FillStyle) {
			if (!color)
			{
				color = FillStyle->GetColor();
			}
			if (color != FillStyle->GetColor())
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
		m_enumerator([&](IFillStyle* FillStyle) {
			FillStyle->SetColor(color);
			return true;
		});
	}

private:
	FillStyleEnumerator m_enumerator;
};