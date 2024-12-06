#include "Drawer.h"
#include <cstdlib>
#include <cassert>

namespace
{

int Sign(int value)
{
	return (0 < value) - (value < 0);
}

/**
 * Рисует крутую прямую (для которой |to.y - from.x| >= |to.x - from.x|).
 */
void DrawSteepLine(Image& image, Point from, Point to, char color)
{
	const int deltaX = std::abs(to.x - from.x);
	const int deltaY = std::abs(to.y - from.y);

	assert(deltaY >= deltaX);

	if (from.y > to.y)
	{ // Крутые прямые рисуются сверху вниз
		std::swap(from, to);
	}

	const int stepX = Sign(to.x - from.x); // Шаг по оси X (-1, 0 или 1).
	const int errorThreshold = deltaY + 1; // Порог увеличения ошибки по оси X.
	const int deltaErr = deltaX + 1;  // Шаг для изменения ошибки.

	// Когда начальное значение ошибки не равно 0, а равно deltaErr/2, прямое движение будет коррелировать с красным.
	int error = deltaErr / 2;

	for (Point p = from; p.y <= to.y; ++p.y)
	{
		image.SetPixel({ p.x, p.y }, color);
		assert((p.y != to.y) || (p.x == to.x));

		error += deltaErr; // Увеличиваем ошибку по оси X.

		if (error >= errorThreshold)
		{ // Если ошибка превысила порог для перехода к следующему целочисленному шагу по оси X
			p.x += stepX; // Смещаемся к следующему целочисленному шагу по оси X
			error -= errorThreshold; // Корректируем ошибку
		}
	}
}

/**
 * Рисует пологую прямую (для которой |to.y - from.x| < |to.y - from.y|).
 */
void DrawSlopeLine(Image& image, Point from, Point to, char color)
{
	const int deltaX = std::abs(to.x - from.x);
	const int deltaY = std::abs(to.y - from.y);

	assert(deltaX >= deltaY);

	if (from.x > to.x)
	{ // Пологие прямые рисуются из правой в левую.
		std::swap(from, to);
	}

	// Пологие прямые рисуются по аналогии с крутыми.

	const int stepY = Sign(to.y - from.y);
	const int errorThreshold = deltaX + 1;
	const int deltaErr = deltaY + 1;

	int error = deltaErr / 2;

	for (Point p = from; p.x <= to.x; ++p.x)
	{
		image.SetPixel({ p.x, p.y }, color);
		assert((p.x != to.x) || (p.y == to.y));

		error += deltaErr;

		if (error >= errorThreshold)
		{
			p.y += stepY;
			error -= errorThreshold;
		}
	}
}

} // namespace

/**
 * Рисует прямую между точками from и to с цветом color на изображении.
 *
 * Для рисования используется алгоритм Брезенхема.
 * (https://ru.wikipedia.org/wiki/Алгоритм_Брезенхема)
 */
void DrawLine(Image& image, Point from, Point to, char color)
{
	const int deltaX = std::abs(to.x - from.x);
	const int deltaY = std::abs(to.y - from.y);

	if (deltaY > deltaX)
	{ // Прямая крутая.
		DrawSteepLine(image, from, to, color);
	}
	else
	{ // Прямая пологая.
		DrawSlopeLine(image, from, to, color);
	}
}

void DrawCircle(Image& image, const Point center, const int radius, const char color)
{
	int x = 0;
	int y = radius;
	int delta = 3 - 2 * y;

	while (y >= x)
	{
		image.SetPixel({ center.x + x, center.y + y }, color);
		image.SetPixel({ center.x - x, center.y + y }, color);
		image.SetPixel({ center.x + x, center.y - y }, color);
		image.SetPixel({ center.x - x, center.y - y }, color);
		image.SetPixel({ center.x + y, center.y + x }, color);
		image.SetPixel({ center.x - y, center.y + x }, color);
		image.SetPixel({ center.x + y, center.y - x }, color);
		image.SetPixel({ center.x - y, center.y - x }, color);

		delta += delta < 0 ? 4 * x + 6 : 4 * (x - y--) + 10;
		++x;
	}
}