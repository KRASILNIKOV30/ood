#pragma once
#include "IShapeBehavior.h"
#include "Point.h"
#include "ICanvas.h"

class TriangleBehavior : public IShapeBehavior
{
public:
	TriangleBehavior(Point vertex1, Point vertex2, Point vertex3);
	void Draw(ICanvas& canvas) const final;
	std::string GetType() const final;
	ShapeParameters GetParams() const final;
	void Move(Point vector) final;
	
private:
	Point m_vertex1, m_vertex2, m_vertex3;
};

