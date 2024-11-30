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
		return GetCompositeStyleValue(std::function([](IFillStyle const& fillStyle) {
			return fillStyle.IsEnabled();
		}));
	}

	void SetEnabled(bool const enabled) override
	{
		m_enumerator([&](auto& fillStyle) {
			fillStyle.SetEnabled(enabled);
			return true;
		});
	}

	// Устранить дублирование с помощью шаблонов (Исправлено)
	[[nodiscard]] std::optional<Color> GetColor() const override
	{
		return GetCompositeStyleValue(std::function([](IFillStyle const& fillStyle) {
			return fillStyle.GetColor();
		}));
	}

	void SetColor(Color const color) override
	{
		m_enumerator([&](auto& fillStyle) {
			fillStyle.SetColor(color);
			return true;
		});
	}

private:
	template <typename T>
	std::optional<T> GetCompositeStyleValue(std::function<std::optional<T>(IFillStyle const&)> const& GetStyle) const;

private:
	FillStyleEnumerator m_enumerator;
};

template <typename T>
std::optional<T> CompositeFillStyle::GetCompositeStyleValue(std::function<std::optional<T>(IFillStyle const&)> const& GetStyle) const
{
	std::optional<T> result = std::nullopt;
	m_enumerator([&](auto const& fillStyle) {
		if (!result.has_value())
		{
			result = GetStyle(fillStyle);
		}
		else if (result != GetStyle(fillStyle))
		{
			result = std::nullopt;
			return false;
		}
		return true;
	});

	return result;
}