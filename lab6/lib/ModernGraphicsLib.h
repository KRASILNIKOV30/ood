#pragma once
#include <ostream>

namespace modern_graphics_lib
{

class Point
{
public:
	Point(const int x, const int y) :x(x), y(y) {}
	int x;
	int y;
};

class RGBAColor
{
public:
	RGBAColor(float const r, float const g, float const b, float const a):r(r), g(g), b(b), a(a){}
	float r, g, b, a;
};

class ModernGraphicsRenderer
{
public:
	explicit ModernGraphicsRenderer(std::ostream & strm) : m_out(strm)
	{
	}

	~ModernGraphicsRenderer()
	{
		if (m_drawing)
		{
			EndDraw();
		}
	}

	void BeginDraw()
	{
		if (m_drawing)
		{
			throw std::logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << std::endl;
		m_drawing = true;
	}

	void DrawLine(const Point & start, const Point & end, const RGBAColor& color) const
	{
		if (!m_drawing)
		{
			throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << "<line fromX=" << start.x << " fromY=" << start.y
			<< " toX=" << end.x << " toY=" << end.y << "/>" << std::endl;
		m_out << std::setprecision(2) << "  <color r=" << color.r << " g=" << color.g << " b=" << color.b << " a=" << color.a << " />" << std::endl;
		m_out << "</line>" << std::endl;
	}

	void EndDraw()
	{
		if (!m_drawing)
		{
			throw std::logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << std::endl;
		m_drawing = false;
	}
private:
	std::ostream & m_out;
	bool m_drawing = false;
};
}
