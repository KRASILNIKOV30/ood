#pragma once
#include "IDrawingStrategy.h"
class LineDrawingStrategy : public IDrawingStrategy
{
public:
	LineDrawingStrategy(Point start, Point end);
	void Draw(ICanvas& canvas) const final;
	std::string GetType() const final;
	ShapeParameters GetParams() const final;
	void Move(Point vector) final;

private:
	Point m_start;
	Point m_end;
};

