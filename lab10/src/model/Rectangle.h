#pragma once
#include "Shape.h"

class Rectangle final : public Shape
{
public:
	explicit Rectangle(std::string const& id, const Frame& frame)
		: Shape(id, frame)
	{
	}

	[[nodiscard]] std::string GetType() const override
	{
		return "rectangle";
	}
};
