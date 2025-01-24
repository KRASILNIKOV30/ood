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

	Frame GetFrame() override
	{
		return m_shape->GetFrame();
	}

	[[nodiscard]] std::string GetId() const override
	{
		return m_shape->GetId();
	}

	[[nodiscard]] bool CheckClick(Point p) const override
	{
		const auto clicked = HitTest(p);
		if (clicked)
		{
			m_shape->Click();
		}
		return clicked;
	}

	[[nodiscard]] virtual bool HitTest(Point p) const = 0;

private:
	IShapeViewModelPtr m_shape;
};