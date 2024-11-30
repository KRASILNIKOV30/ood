#pragma once

#include "IShape.h"
#include "../styles/fillStyle/FillStyle.h"
#include "../styles/lineStyle/LineStyle.h"

class Shape : public IShape
{
public:
	explicit Shape(Frame const& frame, Color const fillColor, Color const lineColor)
		: m_frame(frame)
		, m_lineStyle(std::make_shared<LineStyle>(lineColor))
		, m_fillStyle(std::make_shared<FillStyle>(fillColor))
	{
	}

	Shape(Shape const& shape)
		: m_frame(shape.m_frame)
		, m_lineStyle(std::make_shared<LineStyle>(*shape.m_lineStyle))
		, m_fillStyle(std::make_shared<FillStyle>(*shape.m_fillStyle))
	{}

	void SetFrame(const Frame& frame) override
	{
		m_frame = frame;
	}

	[[nodiscard]] Frame GetFrame() const override
	{
		return m_frame;
	}

	ILineStyle& GetLineStyle() override
	{
		return *m_lineStyle;
	}

	IFillStyle& GetFillStyle() override
	{
		return *m_fillStyle;
	}

	IGroupShapePtr  GetGroup() override
	{
		return nullptr;
	}

	void Draw(const ICanvasPtr canvas) const override
	{
		canvas->SetFillColor(m_fillStyle->GetColor().value());
		canvas->SetLineColor(m_lineStyle->GetColor().value());
		canvas->SetLineWidth(m_lineStyle->GetLineWidth().value());
		DrawShape(canvas);
	}

	virtual void DrawShape(ICanvasPtr canvas) const = 0;

private:
	Frame m_frame;
	std::shared_ptr<LineStyle> m_lineStyle;
	std::shared_ptr<FillStyle> m_fillStyle;
};