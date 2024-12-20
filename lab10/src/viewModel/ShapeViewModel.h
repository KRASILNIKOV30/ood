#pragma once
#include "../appModel/IShapeAppModel.h"
#include "IShapeViewModel.h"

class ShapeViewModel final : public IShapeViewModel
{
public:
	ShapeViewModel(IShapeAppModelPtr shape)
		: m_shape(std::move(shape))
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

	void SetSelected(const bool selected) override
	{
		m_selected = selected;
	}

	void Click() override
	{
		m_clickSignal();
	}

	ScopedConnection DoOnClick(const ClickSignalSlot& slot) override
	{
		return m_clickSignal.connect(slot);
	}

private:
	ClickSignal m_clickSignal;
	IShapeAppModelPtr m_shape;
	bool m_selected = false;
};
