#pragma once
#include "ICanvas.h"

class SvgCanvas final : public ICanvas
{
public:
	SvgCanvas(std::ostream& svgFile);
	~SvgCanvas();
	void MoveTo(Point point);
	void LineTo(Point point);
	void SetColor(Color color);
	void DrawEllipse(Point center, double rx, double ry);

private:
	std::ostream& m_svgFile;
	Color m_color = 0;
	Point m_point = { 0, 0 };
};

