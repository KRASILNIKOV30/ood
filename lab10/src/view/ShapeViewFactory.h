#pragma once
#include "ShapeView.h"
#include "shapes/RectangleView.h"

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

		throw std::runtime_error("Unknown type");
	}
};