#pragma once
#include "../../Frame.h"
#include "../../model/IShape.h"
#include "../AbstractUndoableEdit.h"

class ReframeEdit final : public AbstractUndoableEdit
{
public:
	ReframeEdit(IShapePtr const& shape, Frame const& prevFrame)
		: m_shape(shape)
		, m_frame(shape->GetFrame())
		, m_prevFrame(prevFrame)
	{
	}

	void UndoImpl() override
	{
		m_shape->Reframe(m_prevFrame);
	}

	void RedoImpl() override
	{
		m_shape->Reframe(m_frame);
	}

	bool ReplaceEditImpl(const IUndoableEditPtr& edit) override
	{
		if (const auto reframe = dynamic_cast<const ReframeEdit*>(edit.get()))
		{
			if (reframe->m_shape == m_shape)
			{
				m_prevFrame = reframe->m_prevFrame;
				return true;
			}
		}
		return false;
	}

private:
	IShapePtr m_shape;
	Frame m_frame;
	Frame m_prevFrame;
};
