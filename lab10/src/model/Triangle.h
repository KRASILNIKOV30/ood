#pragma once
#include "Shape.h"

class Triangle final : public Shape
{
public:
	explicit Triangle(const Frame& frame)
		: Shape(frame)
	{
	}

	[[nodiscard]] std::string GetType() const override
	{
		return "triangle";
	}
};
