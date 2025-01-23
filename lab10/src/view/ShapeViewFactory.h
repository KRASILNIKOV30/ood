#pragma once
#include "../viewModel/IShapeViewModel.h"
#include "IShapeView.h"
#include "shapes/EllipseView.h"
#include "shapes/RectangleView.h"
#include "shapes/TriangleView.h"

class ShapeViewFactory
{
public:
	static IShapeViewPtr CreateShape(QWidget* parent, const IShapeViewModelPtr& shape)
	{
		const auto type = shape->GetType();
		if (type == "rectangle")
		{
			return std::make_shared<RectangleView>(parent, shape);
		}
		if (type == "ellipse")
		{
			return std::make_shared<EllipseView>(parent, shape);
		}
		if (type == "triangle")
		{
			return std::make_shared<TriangleView>(parent, shape);
		}

		throw std::runtime_error("Unknown shape");
	}
};