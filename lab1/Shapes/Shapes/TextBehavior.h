#pragma once
#include "IShapeBehavior.h"
class TextBehavior : public IShapeBehavior
{
public:
	TextBehavior(Point leftTop, double fontSize, std::string text);
	void Draw(ICanvas& canvas) const final;
	std::string GetType() const final;
	ShapeParameters GetParams() const final;
	void Move(Point vector) final;

private:
	Point m_leftTop;
	double m_fontSize;
	std::string m_text;
};

