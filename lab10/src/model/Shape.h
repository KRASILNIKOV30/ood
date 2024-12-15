#pragma once
#include "../Frame.h"
#include "IShape.h"

class Shape : public IShape
{
public:
	// ReSharper disable once CppNonExplicitConvertingConstructor
	Shape(const Frame& frame)
		: m_frame(frame)
	{
	}

	[[nodiscard]] Frame GetFrame() const override
	{
		return m_frame;
	}

private:
	Frame m_frame;
};