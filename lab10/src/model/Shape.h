#pragma once
#include "../Frame.h"
#include "IShape.h"

class Shape : public IShape
{
public:
	Shape(std::string id, const Frame& frame)
		: m_frame(frame)
		, m_id(std::move(id))
	{
	}

	[[nodiscard]] Frame GetFrame() const override
	{
		return m_frame;
	}

	[[nodiscard]] std::string GetId() const override
	{
		return m_id;
	}

private:
	Frame m_frame;
	std::string m_id;
};