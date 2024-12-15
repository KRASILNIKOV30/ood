#pragma once
#include "../Frame.h"
#include <string>

class Shape
{
public:
	// ReSharper disable once CppNonExplicitConvertingConstructor
	Shape(const Frame& frame)
		: m_frame(frame)
	{
	}

	virtual ~Shape() = default;

	[[nodiscard]] Frame GetFrame() const
	{
		return m_frame;
	}

	[[nodiscard]] virtual std::string GetType() const = 0;

private:
	Frame m_frame;
};