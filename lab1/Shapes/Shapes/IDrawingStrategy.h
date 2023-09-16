#pragma once
#include "ICanvas.h"

class IDrawingStrategy
{
public:
	virtual void Draw(ICanvas& canvas) = 0;
	~IDrawingStrategy() = default;
};