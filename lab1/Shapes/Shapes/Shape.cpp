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

void Shape::SetDrawingStrategy(std::unique_ptr<IDrawingStrategy>&& drawingStrategy)
{
	m_drawingStrategy = std::move(drawingStrategy);
}

Shape::Shape(Shape const& rhs)
{
}

std::string Shape::GetType() const
{
	return m_drawingStrategy->GetType();
}

ShapeParameters Shape::GetParams() const
{
	return m_drawingStrategy->GetParams();
}

void Shape::Move(Point vector)
{
	m_drawingStrategy->Move(vector);
}
