#include "SvgCanvas.h"

SvgCanvas::SvgCanvas(std::ostream& svgFile)
    : m_svgFile(svgFile)
{
    SetColor(m_color);
    m_svgFile << "<svg width=\"1200\" height=\"800\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
}

SvgCanvas::~SvgCanvas()
{
    m_svgFile << "</svg>" << std::endl;
}

void SvgCanvas::MoveTo(Point point)
{
    m_point = point;
}

void SvgCanvas::LineTo(Point point)
{
    m_svgFile << "<line x1=\"" << m_point.x << "\" y1=\"" << m_point.y << "\" ";
    m_svgFile << "x2 =\"" << point.x << "\" y2=\"" << point.y << "\" ";
    m_svgFile << "style=\"stroke:#" << GetHexStrFromUint32(m_color, COLOR_LEN) << ";stroke-width:3\"/>" << std::endl;
    m_point = point;
}

void SvgCanvas::SetColor(Color color)
{
    m_color = color;
}

void SvgCanvas::DrawEllipse(Point center, double rx, double ry)
{
    m_svgFile << "<ellipse cx=\"" << center.x << "\" cy=\"" << center.y << "\" ";
    m_svgFile << "rx=\"" << rx << "\" ry=\"" << ry << "\" ";
    m_svgFile << "style=\"fill:transparent;stroke:#" << GetHexStrFromUint32(m_color, COLOR_LEN) << ";stroke-width:3\"/>" << std::endl;
}
