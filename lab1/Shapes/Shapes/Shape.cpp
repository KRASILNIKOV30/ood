#include "Shape.h"

Shape::Shape(std::unique_ptr<IShapeBehavior>&& drawingStrategy, Color color)
	: m_drawingStrategy(std::move(drawingStrategy))
	, m_color(color)
{
}

void Shape::Draw(ICanvas& canvas)
{
	canvas.SetColor(m_color);
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

void Shape::SetDrawingStrategy(std::unique_ptr<IShapeBehavior>&& drawingStrategy)
{
	m_drawingStrategy = std::move(drawingStrategy);
}

std::string Shape::GetType() const
{
	return m_drawingStrategy->GetType();
}

ShapeParameters Shape::GetParams() const
{
	return m_drawingStrategy->GetParams();
}

void Shape::Move(double dx, double dy)
{
	m_drawingStrategy->Move(dx, dy);
}
