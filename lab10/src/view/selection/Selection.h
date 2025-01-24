#pragma once
#include "../canvas/ICanvas.h"
#include "ISelection.h"

class Selection final : public ISelection
{
public:
	void Draw(wxDC& dc, const Frame& frame) override;

private:
	ICanvasPtr m_canvas;
};