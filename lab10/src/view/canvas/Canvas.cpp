#include "Canvas.h"
#include "../ShapeViewFactory.h"
#include "../selection/Selection.h"

Canvas::Canvas(wxWindow* parent, IShapesViewModelPtr const& shapes)
	: wxPanel(parent)
	, m_model(shapes)
{
	wxWindow::SetBackgroundStyle(wxBG_STYLE_PAINT);

	m_addShapesConnection = m_model->DoOnAddShape([&](const auto& shape, size_t pos) {
		DoAddShape(shape, pos);
	});
	m_removeShapesConnection = m_model->DoOnRemoveShape([&](const auto& id) {
		DoRemoveShape(id);
	});
	m_selectedIdConnection = m_model->DoOnSelectionChange([&](const auto& id) {
		Refresh();
	});
}

void Canvas::AddShape(const std::string& type)
{
	m_model->AddShape(type);
}

void Canvas::DoAddShape(const IShapeViewModelPtr& shapeModel, size_t pos)
{
	const auto shape = ShapeViewFactory::CreateShapeView(shapeModel);
	m_shapes.Insert(shape, pos);
	Refresh();
}

void Canvas::DoRemoveShape(const std::string& id)
{
	m_shapes.Remove(id);
}

void Canvas::DrawSelection(wxDC& dc)
{
	const auto selectedShapeId = m_model->GetSelectedShapeId();
	if (!selectedShapeId.has_value())
	{
		return;
	}
	const auto shape = m_shapes.Get(selectedShapeId.value());
	const auto frame = shape->GetFrame();
	m_selection->Draw(dc, frame);
}

void Canvas::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	DrawSelection(dc);
	m_shapes.ForEach([&](const IShapeViewPtr& shapeView) {
		shapeView->Draw(dc);
		return true;
	});
}

void Canvas::OnMouseDown(wxMouseEvent& event)
{
	Point p{ event.GetX(), event.GetY() };

	m_shapes.ForEach([&](const IShapeViewPtr& shapeView) {
		return !shapeView->CheckClick(p);
	});
}

wxBEGIN_EVENT_TABLE(Canvas, wxPanel)
	EVT_PAINT(Canvas::OnPaint)
		EVT_LEFT_DOWN(Canvas::OnMouseDown)
			wxEND_EVENT_TABLE()
