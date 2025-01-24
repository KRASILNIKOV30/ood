#pragma once
#include <utility>

#include "../viewModel/IShapeViewModel.h"
#include "IShapeView.h"

class ShapeView : public IShapeView
{
public:
	explicit ShapeView(IShapeViewModelPtr shape)
		: m_shape(std::move(shape))
	{
	}

	[[nodiscard]] Frame GetFrame() const override
	{
		return m_shape->GetFrame();
	}

	[[nodiscard]] std::string GetId() const override
	{
		return m_shape->GetId();
	}

	[[nodiscard]] bool CheckMouseDown(Point p, bool ctrl) const override
	{
		const auto clicked = HitTest(p);
		if (clicked)
		{
			m_shape->Click(p, ctrl);
		}
		return clicked;
	}

	[[nodiscard]] virtual bool HitTest(Point p) const = 0;

	void MouseMove(Point const p) const override
	{
		m_shape->Drag(p);
	}

	void MouseUp(Point const p) const override
	{
		m_shape->Drop(p);
	}

private:
	IShapeViewModelPtr m_shape;
	ScopedConnection m_reframeConnection;
};