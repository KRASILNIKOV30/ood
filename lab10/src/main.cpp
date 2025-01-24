#include "appModel/IShapesAppModel.h"
#include "appModel/ShapesAppModel.h"
#include "model/IShapes.h"
#include "model/Shapes.h"
#include "view/canvas/Canvas.h"
#include "viewModel/IShapesViewModel.h"
#include "viewModel/ShapesViewModel.h"

#include <memory>
#include <utility>
#include <vector>
#include <wx/wx.h>

class MyFrame final : public wxFrame
{
public:
	MyFrame(IShapesViewModelPtr model)
		: wxFrame(NULL, wxID_ANY, "Shapes", wxDefaultPosition, wxSize(800, 600))
		, m_model(std::move(model))
	{
		m_canvas = std::make_shared<Canvas>(this, m_model);
		SetSize(800, 600);
		const auto panel = new wxPanel(this);
		const auto sizer = new wxBoxSizer(wxHORIZONTAL);

		const auto btnRectangle = new wxButton(panel, wxID_ANY, "Add rectangle");
		const auto btnEllipse = new wxButton(panel, wxID_ANY, "Add ellipse");
		const auto btnTriangle = new wxButton(panel, wxID_ANY, "Add triangle");

		btnRectangle->Bind(wxEVT_BUTTON, &MyFrame::OnRectangleClicked, this);
		btnEllipse->Bind(wxEVT_BUTTON, &MyFrame::OnEllipseClicked, this);
		btnTriangle->Bind(wxEVT_BUTTON, &MyFrame::OnTriangleClicked, this);

		sizer->Add(btnRectangle, 1, wxALL | wxCENTER, 10);
		sizer->Add(btnEllipse, 1, wxALL | wxCENTER, 10);
		sizer->Add(btnTriangle, 1, wxALL | wxCENTER, 10);
		panel->SetSizer(sizer);

		const auto mainSizer = new wxBoxSizer(wxVERTICAL);
		mainSizer->Add(panel, 0, wxEXPAND | wxALL, 5);
		mainSizer->Add(m_canvas.get(), 1, wxEXPAND | wxALL, 10);

		SetSizer(mainSizer);
	}

private:
	void OnRectangleClicked(wxCommandEvent& event)
	{
		m_canvas->AddShape("rectangle");
	}

	void OnEllipseClicked(wxCommandEvent& event)
	{
		m_canvas->AddShape("ellipse");
	}

	void OnTriangleClicked(wxCommandEvent& event)
	{
		m_canvas->AddShape("triangle");
	}

	std::shared_ptr<Canvas> m_canvas;
	IShapesViewModelPtr m_model;
};

class MyApp final : public wxApp
{
public:
	virtual bool OnInit()
	{
		m_model = std::make_unique<Shapes>();
		m_appModel = std::make_shared<ShapesAppModel>(m_model.get());
		m_viewModel = std::make_shared<ShapesViewModel>(m_appModel);
		m_frame = std::make_unique<MyFrame>(m_viewModel);
		m_frame->Show(true);
		return true;
	}

private:
	std::unique_ptr<IShapes> m_model;
	IShapesAppModelPtr m_appModel;
	IShapesViewModelPtr m_viewModel;
	std::shared_ptr<Canvas> m_canvas;
	std::unique_ptr<MyFrame> m_frame;
};

wxIMPLEMENT_APP(MyApp);
