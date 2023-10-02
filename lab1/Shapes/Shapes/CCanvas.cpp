#include "CCanvas.h"
#include "Common.h"

CCanvas::CCanvas(std::ostream& svgFile)
    : m_svgFile(svgFile)
{
    SetColor(m_color);
    m_svgFile << "<svg width=\"1200\" height=\"800\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
}

CCanvas::~CCanvas()
{
    m_svgFile << "</svg>" << std::endl;
}

void CCanvas::MoveTo(Point point)
{
    m_point = point;
}

void CCanvas::LineTo(Point point)
{
    m_svgFile << "<line x1=\"" << m_point.x << "\" y1=\"" << m_point.y << "\" ";
    m_svgFile << "x2 =\"" << point.x << "\" y2=\"" << point.y << "\" ";
    m_svgFile << "style=\"stroke:#" << GetHexStrFromUint32(m_color, COLOR_LEN) << ";stroke-width:3\"/>" << std::endl;
    m_point = point;
}

void CCanvas::SetColor(Color color)
{
    m_color = color;
}

void CCanvas::DrawEllipse(Point center, double rx, double ry)
{
    m_svgFile << "<ellipse cx=\"" << center.x << "\" cy=\"" << center.y << "\" ";
    m_svgFile << "rx=\"" << rx << "\" ry=\"" << ry << "\" ";
    m_svgFile << "style=\"fill:transparent;stroke:#" << GetHexStrFromUint32(m_color, COLOR_LEN) << ";stroke-width:3\"/>" << std::endl;
}

void CCanvas::DrawText(Point leftTop, double fontSize, std::string text)
{
    m_svgFile << "<text x=\"" << leftTop.x << "\" y=\"" << leftTop.y << "\" ";
    m_svgFile << "style=\"color:#" << GetHexStrFromUint32(m_color, COLOR_LEN) << ";font-size:" << fontSize << "\">";
    m_svgFile << text << "</text>" << std::endl;
}
