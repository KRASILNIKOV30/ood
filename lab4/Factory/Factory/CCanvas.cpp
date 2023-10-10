#include "CCanvas.h"
#include "Color.h"

CCanvas::CCanvas(std::ostream& svgFile)
	: m_svgFile(svgFile)
{
	m_svgFile << R"(<svg width="1200" height="800" version="1.1" xmlns="http://www.w3.org/2000/svg">)" << std::endl;
}

CCanvas::~CCanvas()
{
    m_svgFile << "</svg>" << std::endl;
}

void CCanvas::DrawLine(const Point from, const Point to)
{
    m_svgFile << "<line x1=\"" << from.x << "\" y1=\"" << from.y << "\" ";
    m_svgFile << "x2 =\"" << to.x << "\" y2=\"" << to.y << "\" ";
    m_svgFile << "style=\"stroke:" << ColorToStr(m_color) << ";stroke-width:3\"/>" << std::endl;
}

void CCanvas::SetColor(const Color color)
{
    m_color = color;
}

void CCanvas::DrawEllipse(const Point leftTop, const double w, const double h)
{
    const auto center = leftTop + Point{ w / 2, h / 2 };
    const double rx = w / 2;
    const double ry = h / 2;
    m_svgFile << "<ellipse cx=\"" << center.x << "\" cy=\"" << center.y << "\" ";
    m_svgFile << "rx=\"" << rx << "\" ry=\"" << ry << "\" ";
    m_svgFile << "style=\"fill:transparent;stroke:" << ColorToStr(m_color) << ";stroke-width:3\"/>" << std::endl;
}
