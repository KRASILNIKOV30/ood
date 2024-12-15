#pragma once
#include "Shape.h"

class Rectangle final : public Shape
{
public:
	explicit Rectangle(const Frame& frame)
		: Shape(frame)
	{
	}

	[[nodiscard]] std::string GetType() const override
	{
		return "rectangle";
	}
};
