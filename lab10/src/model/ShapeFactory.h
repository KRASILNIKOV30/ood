#pragma once
#include "Ellipse.h"
#include "Rectangle.h"
#include "Shape.h"
#include "Triangle.h"

constexpr auto DEFAULT_FRAME = Frame{ { 300, 300 }, { 150, 150 } };

class ShapeFactory
{
public:
	IShapePtr CreateShape(std::string const& type)
	{
		if (type == "rectangle")
		{
			return std::make_unique<Rectangle>(std::to_string(m_id++), DEFAULT_FRAME);
		}
		if (type == "triangle")
		{
			return std::make_unique<Triangle>(std::to_string(m_id++), DEFAULT_FRAME);
		}
		if (type == "ellipse")
		{
			return std::make_unique<Ellipse>(std::to_string(m_id++), DEFAULT_FRAME);
		}

		throw std::invalid_argument("Invalid shape type");
	}

private:
	size_t m_id = 0;
};
