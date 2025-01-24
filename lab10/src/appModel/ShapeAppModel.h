#pragma once
#include "../EditSink.h"
#include "../Frame.h"
#include "../history/edit/ReframeEdit.h"
#include "IShapeAppModel.h"

#include <utility>

class ShapeAppModel final : public IShapeAppModel
{
public:
	ShapeAppModel(IShapePtr shape, EditSink editSink)
		: m_shape(std::move(shape))
		, m_sink(std::move(editSink))
	{
	}

	[[nodiscard]] std::string GetId() const override
	{
		return m_shape->GetId();
	}

	[[nodiscard]] Frame GetFrame() const override
	{
		return m_shape->GetFrame();
	}

	[[nodiscard]] std::string GetType() const override
	{
		return m_shape->GetType();
	}

	ScopedConnection DoOnReframe(ReframeSlot const& slot) override
	{
		return m_shape->DoOnReframe(slot);
	}

	void Reframe(Frame const& frame) override
	{
		const auto prevFrame = m_shape->GetFrame();
		m_shape->Reframe(frame);

		m_sink(std::make_shared<ReframeEdit>(m_shape, prevFrame));
	}

private:
	IShapePtr m_shape;
	EditSink m_sink;
};