#pragma once
#include "../../repository/Repository.h"
#include "../../viewModel/IShapesViewModel.h"
#include "../IShapeView.h"
#include "../selection/Selection.h"
#include "ICanvas.h"

#include <wx/wx.h>

class Canvas final
	: public ICanvas
	, public wxPanel
{
public:
	Canvas(wxWindow* parent, IShapesViewModelPtr const& shapes);
	void AddShape(const std::string& type) override;

private:
	void DoAddShape(const IShapeViewModelPtr& shapeModel, size_t pos);
	void DoRemoveShape(const std::string& id);
	void DrawSelection(wxDC& dc);

	void OnPaint(wxPaintEvent& event);
	void OnMouseDown(wxMouseEvent& event);

private:
	Repository<IShapeView> m_shapes;
	IShapesViewModelPtr m_model;
	ScopedConnection m_addShapesConnection;
	ScopedConnection m_removeShapesConnection;
	ScopedConnection m_selectedIdConnection;
	ISelectionPtr m_selection = std::make_shared<Selection>();

	wxDECLARE_EVENT_TABLE();
};
