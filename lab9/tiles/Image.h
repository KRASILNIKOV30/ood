#pragma once
#include "Cow.h"
#include <iosfwd>
#include <string>
#include "Geom.h"
#include "Tile.h"
#include <vector>
#include <filesystem>

class Image
{
public:
	/**
	 * Конструирует изображение заданного размера. Если размеры не являются положительными,
	 * выбрасывает исключение std::out_of_range.
	 */
	explicit Image(Size size, uint32_t color = ' ');

	// Возвращает размер изображения в пикселях.
	[[nodiscard]] Size GetSize() const noexcept;

	/**
	 * Возвращает «цвет» пикселя в указанных координатах. Если координаты выходят за пределы
	 * изображения, возвращает «пробел».
	 */
	[[nodiscard]] uint32_t GetPixel(Point p) const noexcept;

	/**
	 * Задаёт «цвет» пикселя в указанных координатах. Если координаты выходят за пределы изображения
	 * действие игнорируется.
	 */
	void SetPixel(Point p, uint32_t color);

private:
	bool IsPointInImage(Point p) const noexcept;

private:
	Size m_size;
	std::vector<std::vector<CoW<Tile>>> m_tiles;
};

/**
 * Выводит в поток out изображение в виде символов.
 */
void Print(const Image& img, std::ostream& out);

void Save(const Image& img, std::filesystem::path const& filename);

/**
 * Загружает изображение из pixels. Линии изображения разделяются символами \n.
 * Размеры картинки определяются по количеству переводов строки и самой длинной линии.
 */
Image LoadImage(const std::string& pixels);
