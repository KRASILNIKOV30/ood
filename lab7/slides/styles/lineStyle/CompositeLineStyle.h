#pragma once
#include <utility>

#include "ILineStyle.h"
#include "LineStyle.h"
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
		m_enumerator([&](const ILineStyle* lineStyle) {
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

	void setEnabled(bool enabled) override;
	[[nodiscard]] Color GetColor() const override;
	void SetColor(Color color) override;
	[[nodiscard]] double GetLineWidth() const override;
	void SetLineWidth(int width) override;

private:
	LineStyleEnumerator m_enumerator;
};