#include "Image.h"
#include "./Color.h"
#include <cassert>
#include <cmath>
#include <format>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <fstream>

/**
 * Конструирует изображение заданного размера. Если размеры не являются положительными,
 * выбрасывает исключение std::out_of_range.
 */
Image::Image(const Size size, const uint32_t color)
	: m_size(size)
{
	if (size.width < 0 || size.height < 0)
	{
		throw std::out_of_range("Invalid size");
	}
	const int tilesInRow = std::ceil(static_cast<double>(size.width) / Tile::SIZE);
	const int tilesInColumn = std::ceil(static_cast<double>(size.height) / Tile::SIZE);
	const CoW tile{Tile(color)};
	const auto row = std::vector(tilesInRow, tile);
	m_tiles = std::vector(tilesInColumn, row);
}

Size Image::GetSize() const noexcept
{
	return m_size;
}

/**
 * Возвращает «цвет» пикселя в указанных координатах. Если координаты выходят за пределы
 * изображения, возвращает «пробел».
 */
uint32_t Image::GetPixel(const Point p) const noexcept
{
	if (!IsPointInImage(p))
	{
		return ' ';
	}
	return m_tiles[p.y / Tile::SIZE][p.x / Tile::SIZE]->GetPixel({ p.x % Tile::SIZE, p.y % Tile::SIZE });
}

/**
 * Задаёт «цвет» пикселя в указанных координатах. Если координаты выходят за пределы изображения
 * действие игнорируется.
 */
void Image::SetPixel(const Point p, const uint32_t color)
{
	if (!IsPointInImage(p))
	{
		return;
	}
	m_tiles[p.y / Tile::SIZE][p.x / Tile::SIZE].Write()->SetPixel({ p.x % Tile::SIZE, p.y % Tile::SIZE }, color);
}

bool Image::IsPointInImage(Point p) const noexcept
{
	return IsPointInSize(p, m_size);
}

/**
 * Выводит в поток out изображение в виде символов.
 */
void Print(const Image& img, std::ostream& out)
{
	const auto [width, height] = img.GetSize();
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			out.put(img.GetPixel({ x, y }));
		}
		out.put('\n');
	}
}

void Save(const Image& img, std::filesystem::path const& filename)
{
	std::ofstream file(filename.string());

	const auto [width, height] = img.GetSize();
	file << "P3" << std::endl;
	file << width << ' ' << height << std::endl;
	file << "255" << std::endl;
	
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			const auto [r, g, b] = createRGBColor(img.GetPixel({ x, y }));
			file << std::format("{} {} {}", r, g, b) << std::endl;
		}
	}
}

/**
 * Загружает изображение из pixels. Линии изображения разделяются символами\n.
 * Размеры картинки определяются по количеству переводов строки и самой длинной линии.
 */
Image LoadImage(const std::string& pixels)
{
	std::istringstream s(pixels);
	Size size;
	std::string line;
	while (std::getline(s, line))
	{
		size.width = std::max(size.width, static_cast<int>(line.length()));
		++size.height;
	}

	Image img(size);

	s = std::istringstream(pixels);
	for (int y = 0; y < size.height; ++y)
	{
		if (!std::getline(s, line))
			break;

		int x = 0;
		for (const uint32_t ch : line)
		{
			img.SetPixel({ x++, y }, ch);
		}
	}

	return img;
}
