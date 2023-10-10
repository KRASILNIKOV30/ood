#pragma once
#include "ICanvas.h"
#include <sstream>

class CCanvas final : public ICanvas
{
public:
	explicit CCanvas(std::ostream& svgFile);
	//Не закрывать тег в деструкторе
	~CCanvas() override;
	void DrawLine(const Point from, const Point to) override;
	void SetColor(const Color color) override;
	void DrawEllipse(const Point leftTop, const double w, const double h) override;

private:
	std::ostream& m_svgFile;
	Color m_color = Color::Black;
};

