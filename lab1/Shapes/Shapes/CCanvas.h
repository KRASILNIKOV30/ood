#pragma once
#include "ICanvas.h"
#include "Color.h"
#include "Point.h"

class CCanvas final : public ICanvas
{
public:
	CCanvas(std::ostream& svgFile);
	~CCanvas();
	void MoveTo(Point point);
	void LineTo(Point point);
	void SetColor(Color color);
	void DrawEllipse(Point center, double rx, double ry);
	void DrawText(Point leftTop, double fontSize, std::string text);

private:
	std::ostream& m_svgFile;
	Color m_color = 0;
	Point m_point = { 0, 0 };
};

