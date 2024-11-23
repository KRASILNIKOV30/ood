#include "SvgCanvas.h"

SvgCanvas::SvgCanvas(std::ostream& svgFile)
	: m_svgFile(svgFile)
{
	m_svgFile << R"(<svg width="1200" height="800" version="1.1" xmlns="http://www.w3.org/2000/svg">)" << std::endl;
}

void SvgCanvas::SetFillColor(Color color)
{
	m_fillColor = color;
}

void SvgCanvas::SetLineColor(Color color)
{
	m_lineColor = color;
}

void SvgCanvas::SetLineWidth(double width)
{
	m_lineWidth = width;
}

void SvgCanvas::DrawLine(Point from, Point to)
{
	m_svgFile << "<line x1=\"" << from.x << "\" y1=\"" << from.y << "\" ";
	m_svgFile << "x2=\"" << to.x << "\" y2=\"" << to.y << "\" ";
	m_svgFile << "style=\"stroke:#" << GetHexStrFromUint32(m_lineColor, COLOR_LEN)
			  << ";stroke-width:" << m_lineWidth << "\"/>" << std::endl;
}

void SvgCanvas::DrawEllipse(Frame frame)
{
	double centerX = frame.leftTop.x + frame.width / 2;
	double centerY = frame.leftTop.y + frame.height / 2;
	m_svgFile << "<ellipse cx=\"" << centerX << "\" cy=\"" << centerY << "\" ";
	m_svgFile << "rx=\"" << frame.width / 2 << "\" ry=\"" << frame.height / 2 << "\" ";
	m_svgFile << "style=\"fill:#" << GetHexStrFromUint32(m_fillColor, COLOR_LEN) << ";stroke:#" << GetHexStrFromUint32(m_lineColor, COLOR_LEN)
			  << ";stroke-width:" << m_lineWidth << "\"/>" << std::endl;
}

void SvgCanvas::DrawPolygon(std::vector<Point> points)
{
	if (points.empty()) return;

	m_svgFile << "<polygon points=\"";
	for (const auto& point : points) {
		m_svgFile << point.x << "," << point.y << " ";
	}
	m_svgFile << "\" style=\"fill:#" << GetHexStrFromUint32(m_fillColor, COLOR_LEN) << ";stroke:#" << GetHexStrFromUint32(m_lineColor, COLOR_LEN)
			  << ";stroke-width:" << m_lineWidth << "\"/>" << std::endl;
}

SvgCanvas::~SvgCanvas()
{
	m_svgFile << "</svg>" << std::endl;
}
