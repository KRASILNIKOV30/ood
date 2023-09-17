#pragma once
#include "IDrawingStrategy.h"
class TextDrawingStrategy : public IDrawingStrategy
{
public:
	TextDrawingStrategy(Point leftTop, double fontSize, std::string text);
	void Draw(ICanvas& canvas) const final;

private:
	Point m_leftTop;
	double m_fontSize;
	std::string m_text;
};

