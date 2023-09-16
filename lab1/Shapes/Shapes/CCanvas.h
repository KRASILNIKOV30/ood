#pragma once
#include "ICanvas.h"
#include <SDL2/SDL.h>
#include "Color.h"
#include "Point.h"

class CCanvas final : public ICanvas
{
public:
	CCanvas(SDL_Window* window);
	void MoveTo(Point point);
	void LineTo(Point point);
	void SetColor(Color color);
	void DrawEllipse(Point center, double rx, double ry);
	void DrawText(Point leftTop, double fontSize, std::string text);
	void Render();

private:
	void ParseColor(Color color, Color& red, Color& green, Color& blue) const;

private:
	SDL_Renderer* m_renderer;
	Color m_color = 0;
	Point m_point = { 0, 0 };
};

