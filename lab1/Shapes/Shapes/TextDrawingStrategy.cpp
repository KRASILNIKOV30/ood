#include "TextDrawingStrategy.h"

TextDrawingStrategy::TextDrawingStrategy(Point leftTop, double fontSize, std::string text)
	: m_leftTop(leftTop)
	, m_fontSize(fontSize)
	, m_text(text)
{
}

void TextDrawingStrategy::Draw(ICanvas& canvas) const
{
	canvas.DrawText(m_leftTop, m_fontSize, m_text);
}

std::string TextDrawingStrategy::GetType() const
{
	return "text";
}

ShapeParameters TextDrawingStrategy::GetParams() const
{
	return ShapeParameters{ {m_leftTop.x, m_leftTop.y, m_fontSize}, m_text };
}

void TextDrawingStrategy::Move(Point vector)
{
	m_leftTop += vector;
}
