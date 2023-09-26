#pragma once
#include "ICanvas.h"
#include "ShapeParameters.h"

class IShapeBehavior
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;
	virtual std::string GetType() const = 0;
	virtual ShapeParameters GetParams() const = 0;
	virtual void Move(double dx, double dy) = 0;
	~IShapeBehavior() = default;
};