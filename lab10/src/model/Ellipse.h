#pragma once
#include "Shape.h"

class Ellipse final : public Shape
{
public:
	explicit Ellipse(const Frame& frame)
		: Shape(frame)
	{
	}

	[[nodiscard]] std::string GetType() const override
	{
		return "ellipse";
	}
};
