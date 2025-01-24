#pragma once
#include "../Frame.h"

#include <wx/dc.h>

class IShapeView
{
public:
	[[nodiscard]] virtual std::string GetId() const = 0;
	virtual Frame GetFrame() = 0;
	virtual void Draw(wxDC& dc) const = 0;
	[[nodiscard]] virtual bool CheckMouseDown(Point p) const = 0;

	virtual ~IShapeView() = default;
};

using IShapeViewPtr = std::shared_ptr<IShapeView>;
