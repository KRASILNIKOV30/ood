#pragma once
#include "Shape.h"

class Ellipse final : public Shape
{
public:
	explicit Ellipse(std::string const& id, const Frame& frame)
		: Shape(id, frame)
	{
	}

	[[nodiscard]] std::string GetType() const override
	{
		return "ellipse";
	}
};
