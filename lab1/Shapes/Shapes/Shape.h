#pragma once
#include "IShapeBehavior.h"
#include <memory>

class Shape
{
public:
	Shape(std::unique_ptr<IShapeBehavior>&& drawingStrategy, Color color);
	void Draw(ICanvas& canvas);
	Color GetColor();
	void SetColor(Color color);
	void SetDrawingStrategy(std::unique_ptr<IShapeBehavior>&& drawingStrategy);
	std::string GetType() const;
	ShapeParameters GetParams() const;
	void Move(double dx, double dy);

private:
	std::unique_ptr<IShapeBehavior> m_drawingStrategy;
	Color m_color = 0;
};

