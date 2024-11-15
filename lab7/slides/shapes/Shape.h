#pragma once
#include "IShape.h"
#include "../styles/fillStyle/FillStyle.h"
#include "../styles/lineStyle/LineStyle.h"

class Shape : public IShape
{
public:
	explicit Shape(Frame const& frame, Color const fillColor, Color const lineColor)
		: m_frame(frame)
		, m_lineStyle(lineColor)
		, m_fillStyle(fillColor)
	{
	}

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
		return m_lineStyle;
	}

	IFillStyle& GetFillStyle() override
	{
		return m_fillStyle;
	}

	IGroupShapePtr GetGroup() override
	{
		return nullptr;
	}

	void Draw(const ICanvasPtr canvas) const override
	{
		canvas->SetFillColor(m_fillStyle.GetColor());
		canvas->SetLineColor(m_lineStyle.GetColor());
		canvas->SetLineWidth(m_lineStyle.GetLineWidth());
		DrawShape(canvas);
	}

	virtual void DrawShape(ICanvasPtr canvas) const = 0;

private:
	Frame m_frame;
	LineStyle m_lineStyle;
	FillStyle m_fillStyle;
};