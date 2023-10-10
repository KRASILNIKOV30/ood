#pragma once
#include <istream>

#include "CPainter.h"
#include "ICanvas.h"
#include "IDesigner.h"

class CClient
{
public:
	CClient(std::istream& stream, ICanvas& canvas)
		: m_stream(stream)
		, m_canvas(canvas)
	{
	}

	void MakePicture(IDesigner const& designer, CPainter const& painter) const
	{
		painter.DrawPicture(designer.CreateDraft(m_stream), m_canvas);
	}

private:
	std::istream& m_stream;
	ICanvas& m_canvas;
};
