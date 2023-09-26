#pragma once
#include "IShapeBehavior.h"
class RectangleBehavior : public IShapeBehavior
{
public:
	RectangleBehavior(Point leftTop, double width, double height);
	void Draw(ICanvas& canvas) const final;
	std::string GetType() const final;
	ShapeParameters GetParams() const final;
	void Move(Point vector) final;

private:
	Point m_leftTop;
	double m_width;
	double m_height;
};

