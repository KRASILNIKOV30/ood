#pragma once
#include "../Frame.h"
#include "../model/Shape.h"
#include "IShapeAppModel.h"

class ShapeAppModel final : public IShapeAppModel
{
public:
	ShapeAppModel(IShape* shape)
		: m_shape(shape)
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
	IShape* m_shape;
};