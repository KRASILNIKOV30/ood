#pragma once
#include "IShapeBehavior.h"

class CircleBehavior : public IShapeBehavior
{
public:
	CircleBehavior(Point center, double radius);
	void Draw(ICanvas& canvas) const final;
	std::string GetType() const final;
	ShapeParameters GetParams() const final;
	void Move(Point vector) final;

private:
	Point m_center;
	double m_radius;
};

