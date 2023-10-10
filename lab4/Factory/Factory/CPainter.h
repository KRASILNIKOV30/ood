#pragma once
#include "CPictureDraft.h"

class CPainter
{
public:
	void DrawPicture(CPictureDraft draft, ICanvas& canvas) const
	{
		for (int i = 0; i < draft.GetShapeCount(); i++)
		{
			draft.GetShape(i)->Draw(canvas);
		}
	}
};
