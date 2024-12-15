#pragma once
#include "Shape.h"

class Triangle final : public Shape
{
public:
	explicit Triangle(std::string const& id, const Frame& frame)
		: Shape(id, frame)
	{
	}

	[[nodiscard]] std::string GetType() const override
	{
		return "triangle";
	}
};
