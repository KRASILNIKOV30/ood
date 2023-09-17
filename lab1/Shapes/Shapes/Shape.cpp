#include "Shape.h"

Shape::Shape(std::unique_ptr<IDrawingStrategy>&& drawingStrategy)
	: m_drawingStrategy(std::move(drawingStrategy))
{
}

void Shape::Draw(ICanvas& canvas)
{
	m_drawingStrategy->Draw(canvas);
}

Color Shape::GetColor()
{
	return m_color;
}

void Shape::SetColor(Color color)
{
	m_color = color;
}
