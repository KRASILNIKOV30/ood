#include "RectangleDrawingStrategy.h"

RectangleDrawingStrategy::RectangleDrawingStrategy(Point leftTop, double width, double height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void RectangleDrawingStrategy::Draw(ICanvas& canvas) const
{
	canvas.MoveTo(m_leftTop);
	canvas.LineTo(m_leftTop + Point{ m_width, 0 });
	canvas.LineTo(m_leftTop + Point{ m_width, m_height });
	canvas.LineTo(m_leftTop + Point{ 0, m_height });
	canvas.LineTo(m_leftTop);

}
