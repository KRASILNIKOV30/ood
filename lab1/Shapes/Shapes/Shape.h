#pragma once
#include "IDrawingStrategy.h"
#include <memory>

class Shape
{
public:
	Shape(std::unique_ptr<IDrawingStrategy>&& drawingStrategy, Color color);
	void Draw(ICanvas& canvas);
	Color GetColor();
	void SetColor(Color color);
	void SetDrawingStrategy(std::unique_ptr<IDrawingStrategy>&& drawingStrategy);
	std::string GetType() const;
	ShapeParameters GetParams() const;
	void Move(Point vector);

private:
	std::unique_ptr<IDrawingStrategy> m_drawingStrategy;
	Color m_color = 0;
};

