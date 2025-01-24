#pragma once
#include "ShapeView.h"
#include "shapes/EllipseView.h"
#include "shapes/RectangleView.h"
#include "shapes/TriangleView.h"

class ShapeViewFactory
{
public:
	static IShapeViewPtr CreateShapeView(const IShapeViewModelPtr& shape)
	{
		const auto type = shape->GetType();
		if (type == "rectangle")
		{
			return std::make_shared<RectangleView>(shape);
		}
		if (type == "triangle")
		{
			return std::make_shared<TriangleView>(shape);
		}
		if (type == "ellipse")
		{
			return std::make_shared<EllipseView>(shape);
		}

		throw std::runtime_error("Unknown type");
	}
};