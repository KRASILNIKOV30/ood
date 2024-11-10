#pragma once
#include "lib/GraphicsLib.h"
#include "lib/ModernGraphicsLib.h"

class ModernGraphicsRendererClassAdapter final
	: public graphics_lib::ICanvas
	, modern_graphics_lib::ModernGraphicsRenderer
{
public:
	explicit ModernGraphicsRendererClassAdapter(std::ostream& out)
		: ModernGraphicsRenderer(out)
		,m_color(CreateRGBAColor(0))
		, m_point({ 0, 0 })
	{
	}
	// Добавить вызов BeginDraw (Исправлено)

	void BeginDraw()
	{
		ModernGraphicsRenderer::BeginDraw();
	}

	void EndDraw()
	{
		ModernGraphicsRenderer::EndDraw();
	}

	void SetColor(uint32_t const color) override
	{
		m_color = CreateRGBAColor(color);
	}

	void MoveTo(int const x, int const y) override
	{
		m_point = { x, y };
	}

	void LineTo(int const x, int const y) override
	{
		modern_graphics_lib::Point const to = { x, y };
		DrawLine(m_point, to, m_color);
		m_point = to;
	}

private:
	static modern_graphics_lib::RGBAColor CreateRGBAColor(const uint32_t color)
	{
		// Не преобразовывать в строку (Исправлено)
		constexpr uint32_t blue_offset{ 0x00 };
		constexpr uint32_t green_offset{ 0x08 };
		constexpr uint32_t red_offset{ 0x10 };

		const auto red = GetColor(color, red_offset);
		const auto green = GetColor(color, green_offset);
		const auto blue = GetColor(color, blue_offset);

		return modern_graphics_lib::RGBAColor{ red, green, blue, 1.0f};
	}

	static float GetColor(uint32_t const color, uint32_t const offset)
	{
		constexpr uint32_t byte_mask{ 0xFF };
		const uint32_t mask{ byte_mask << offset };
		return static_cast<float>((color & mask) >> offset & byte_mask) / 0xFF;
	}

private:
	modern_graphics_lib::RGBAColor m_color;
	modern_graphics_lib::Point m_point;
};

