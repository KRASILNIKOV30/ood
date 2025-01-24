#pragma once
#include "../Frame.h"
#include "../signals/SignallingValue.h"
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
		return m_frame.GetValue();
	}

	[[nodiscard]] std::string GetId() const override
	{
		return m_id;
	}

	void Reframe(const Frame frame) override
	{
		m_frame = frame;
	}

	ScopedConnection DoOnReframe(ReframeSlot const& slot) override
	{
		return m_frame.Connect1(slot, false);
	}

private:
	SignallingValue<Frame> m_frame;
	std::string m_id;
};