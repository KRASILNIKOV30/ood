#pragma once
#include "../Frame.h"
#include "../model/Shape.h"
#include "IShapeAppModel.h"
#include <utility>

class ShapeAppModel final : public IShapeAppModel
{
public:
	ShapeAppModel(IShapePtr shape)
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

private:
	IShapePtr m_shape;
};