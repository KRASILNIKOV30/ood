#pragma once
#include "../../Frame.h"

#include <memory>
#include <wx/wx.h>

class ISelection
{
public:
	virtual void Draw(wxDC& dc, Frame const& frame) = 0;

	virtual ~ISelection() = default;
};

using ISelectionPtr = std::shared_ptr<ISelection>;
