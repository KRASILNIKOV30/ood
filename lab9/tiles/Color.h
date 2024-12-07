#pragma once
#include <cstdint>

struct RGBColor
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

inline uint8_t GetColor(uint32_t const color, uint32_t const offset)
{
	constexpr uint32_t byte_mask{ 0xFF };
	const uint32_t mask{ byte_mask << offset };
	return ((color & mask) >> offset) & byte_mask;
}

inline RGBColor createRGBColor(const uint32_t color)
{
	constexpr uint32_t blueOffset{ 0x00 };
	constexpr uint32_t greenOffset{ 0x08 };
	constexpr uint32_t redOffset{ 0x10 };

	const auto red = GetColor(color, redOffset);
	const auto green = GetColor(color, greenOffset);
	const auto blue = GetColor(color, blueOffset);

	return RGBColor{ red, green, blue };
}
