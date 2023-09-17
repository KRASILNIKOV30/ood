#pragma once
#include "IDrawingStrategy.h"
class LineDrawingStrategy : public IDrawingStrategy
{
public:
	LineDrawingStrategy(Point start, Point end);
	void Draw(ICanvas& canvas) const final;

private:
	Point m_start;
	Point m_end;
};

