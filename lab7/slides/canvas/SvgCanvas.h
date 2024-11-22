#pragma once
#include "ICanvas.h"

class SvgCanvas final : public ICanvas
{
public:
	explicit SvgCanvas(std::ostream& svgFile);
	void SetFillColor(Color color) override;
	void SetLineColor(Color color) override;
	void SetLineWidth(double width) override;
	void DrawLine(Point from, Point to) override;
	void DrawEllipse(Frame frame) override;
	void DrawPolygon(std::vector<Point> points) override;

	~SvgCanvas() override;

private:
	std::ostream& m_svgFile;
	Color m_color = 0;
	Point m_point = { 0, 0 };
	double m_lineWidth = 1;
};

