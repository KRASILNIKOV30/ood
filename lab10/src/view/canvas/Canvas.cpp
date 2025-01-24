#include "Canvas.h"
#include "../ShapeViewFactory.h"
#include "../selection/Selection.h"

Canvas::Canvas(wxWindow* parent, IShapesViewModelPtr const& shapes)
	: wxPanel(parent)
	, m_model(shapes)
{
	wxNavigationEnabled<wxWindow>::SetFocus();
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
	m_updateConnection = m_model->DoOnUpdate([&]() {
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
	Refresh();
}

void Canvas::DrawSelection(wxDC& dc)
{
	const auto selectedShapeId = m_model->GetSelectedShapeId();
	if (!selectedShapeId.has_value())
	{
		return;
	}
	const auto shape = m_shapes.Find(selectedShapeId.value());
	if (!shape.has_value())
	{
		return;
	}
	const auto frame = shape.value()->GetFrame();
	m_selection->Draw(dc, frame);
}

void Canvas::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	m_shapes.ForEach([&](const IShapeViewPtr& shapeView) {
		shapeView->Draw(dc);
		return true;
	});
	DrawSelection(dc);
}

void Canvas::OnMouseDown(wxMouseEvent& event)
{
	SetFocus();
	const Point p{ event.GetX(), event.GetY() };

	m_shapes.ForEach([&](const IShapeViewPtr& shapeView) {
		return !shapeView->CheckMouseDown(p);
	});
}

void Canvas::OnMouseMove(wxMouseEvent& event)
{
	const Point p{ event.GetX(), event.GetY() };

	m_shapes.ForEach([&](const IShapeViewPtr& shapeView) {
		shapeView->MouseMove(p);
		return true;
	});
}

void Canvas::OnMouseUp(wxMouseEvent& event)
{
	const Point p{ event.GetX(), event.GetY() };

	m_shapes.ForEach([&](const IShapeViewPtr& shapeView) {
		shapeView->MouseUp(p);
		return true;
	});
}

void Canvas::OnKeyDown(wxKeyEvent& event)
{
	if (event.GetModifiers() == wxMOD_CONTROL && event.GetKeyCode() == 'Z')
	{
		m_model->Undo();
	}
	if (event.GetModifiers() == wxMOD_CONTROL && event.GetKeyCode() == 'Y')
	{
		m_model->Redo();
	}
	event.Skip();
}

wxBEGIN_EVENT_TABLE(Canvas, wxPanel)
	EVT_PAINT(Canvas::OnPaint)
		EVT_LEFT_DOWN(Canvas::OnMouseDown)
			EVT_KEY_DOWN(Canvas::OnKeyDown)
				EVT_MOTION(Canvas::OnMouseMove)
					EVT_LEFT_UP(Canvas::OnMouseUp)
						wxEND_EVENT_TABLE()
