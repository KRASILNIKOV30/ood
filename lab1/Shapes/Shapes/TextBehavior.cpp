#include "TextBehavior.h"

TextBehavior::TextBehavior(Point leftTop, double fontSize, std::string text)
	: m_leftTop(leftTop)
	, m_fontSize(fontSize)
	, m_text(text)
{
}

void TextBehavior::Draw(ICanvas& canvas) const
{
	canvas.DrawText(m_leftTop, m_fontSize, m_text);
}

std::string TextBehavior::GetType() const
{
	return "text";
}

ShapeParameters TextBehavior::GetParams() const
{
	return ShapeParameters{ {m_leftTop.x, m_leftTop.y, m_fontSize}, m_text };
}

void TextBehavior::Move(Point vector)
{
	m_leftTop += vector;
}
