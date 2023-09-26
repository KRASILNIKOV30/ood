#pragma once
#include "IShapeBehavior.h"
class LineBehavior : public IShapeBehavior
{
public:
	LineBehavior(Point start, Point end);
	void Draw(ICanvas& canvas) const final;
	std::string GetType() const final;
	ShapeParameters GetParams() const final;
	void Move(double dx, double dy) final;

private:
	Point m_start;
	Point m_end;
};

