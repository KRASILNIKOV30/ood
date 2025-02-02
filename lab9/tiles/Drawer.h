#pragma once
#include "Image.h"

/**
 * Рисует отрезок прямой линии между точками from и to цветом color на изображении Image.
 *
 * Для рисования используется алгоритм Брезенхэма.
 * (https://ru.wikipedia.org/wiki/Алгоритм_Брезенхэма)
 */
void DrawLine(Image& image, Point from, Point to, uint32_t color);

void DrawRect(Image& image, Point leftTop, Size size, uint32_t color);

void FillRect(Image& image, Point leftTop, Size size, uint32_t color);

void DrawCircle(Image& image, Point center, int radius, uint32_t color);

void FillCircle(Image& image, Point center, int radius, uint32_t color);