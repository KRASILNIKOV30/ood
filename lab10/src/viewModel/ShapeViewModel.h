#pragma once
#include "../appModel/IShapeAppModel.h"
#include "IShapeViewModel.h"

class ShapeViewModel final : public IShapeViewModel
{
public:
	ShapeViewModel(IShapeAppModelPtr shape)
		: m_shape(std::move(shape))
	{
		m_reframeConnection = m_shape->DoOnReframe([&](const auto& frame) {
			m_frame = frame;
		});
	}

	[[nodiscard]] std::string GetId() const override
	{
		return m_shape->GetId();
	}

	[[nodiscard]] Frame GetFrame() const override
	{
		return m_frame.GetValue();
	}

	[[nodiscard]] std::string GetType() const override
	{
		return m_shape->GetType();
	}

	ScopedConnection DoOnClick(const ClickSignalSlot& slot) override
	{
		return m_clickSignal.connect(slot);
	}

	ScopedConnection DoOnReframe(const ReframeSlot& slot) override
	{
		return m_frame.Connect1(slot, false);
	}

	void Click(const Point p) override
	{
		m_clickSignal();
		m_startPosition = p;
	}

	void Drag(const Point p) override
	{
		if (!m_startPosition.has_value())
		{
			return;
		}
		const auto start = m_startPosition.value();
		const auto [position, size] = m_frame.GetValue();
		const auto delta = p - start;
		const auto newPos = position + delta;
		Reframe({ newPos, size });
		m_startPosition = p;
	}

	void Drop(const Point p) override
	{
		if (!m_startPosition.has_value())
		{
			return;
		}
		const auto start = m_startPosition.value();
		const auto [position, size] = m_frame.GetValue();
		const auto newPos = position + p - start;
		Reframe({ newPos, size });
		ApplyReframe(m_frame.GetValue());
		m_startPosition.reset();
	}

	void Reframe(const Frame& frame) override
	{
		m_frame = frame;
	}

	void ApplyReframe(const Frame& frame) override
	{
		m_shape->Reframe(frame);
	}

private:
	SignallingValue<Frame> m_frame;
	ScopedConnection m_reframeConnection;
	ClickSignal m_clickSignal;
	IShapeAppModelPtr m_shape;
	bool m_selected = false;
	std::optional<Point> m_startPosition = std::nullopt;
};