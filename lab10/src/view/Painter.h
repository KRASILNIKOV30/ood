#pragma once
#include "../repository/Repository.h"
#include "../viewModel/IShapesViewModel.h"
#include "IPainter.h"
#include "ShapeViewFactory.h"

#include <QPushButton>
#include <QWidget>

class Painter final
	: public QWidget
	, public IPainter
{
	Q_OBJECT

public:
	explicit Painter(
		QWidget* parent,
		IShapesViewModelPtr shapesViewModel,
		const QPushButton* m_rectangle,
		const QPushButton* m_triangle,
		const QPushButton* m_ellipse)
		: QWidget(parent)
		, m_shapesViewModel(std::move(shapesViewModel))
		, m_parent(parent)
	{
		connect(m_rectangle, &QPushButton::clicked, this, [&]() { AddShape("rectangle"); });
		connect(m_triangle, &QPushButton::clicked, this, [&]() { AddShape("triangle"); });
		connect(m_ellipse, &QPushButton::clicked, this, [&]() { AddShape("ellipse"); });

		setBackgroundRole(QPalette::Base);
		setAutoFillBackground(true);
		parent->setStyleSheet("background-color: rgb(255, 255, 255);");
		setFixedSize(800, 600);

		m_addShapesConnection = m_shapesViewModel->DoOnAddShape([&](const auto& shape, size_t pos) {
			AddShape(shape, pos);
		});
		m_removeShapesConnection = m_shapesViewModel->DoOnRemoveShape([&](const auto& id) {
			RemoveShape(id);
		});
		m_selectedIdConnection = m_shapesViewModel->DoOnSelectionChange([&](const auto& id) {
			m_selectionChangeSignal();
		});
	}

	void AddShape(std::string const& type) override
	{
		m_shapesViewModel->AddShape(type);
	}

	ScopedConnection DoOnSelectionChange(const SelectionChangeSlot& slot) override
	{
		return m_selectionChangeSignal.connect(slot);
	}

	std::optional<IShapeViewPtr> GetSelectedShape() override
	{
		const auto selectedShapeId = m_shapesViewModel->GetSelectedShapeId();
		if (!selectedShapeId.has_value())
		{
			return std::nullopt;
		}
		return m_shapes.Get(selectedShapeId.value());
	}

private:
	void paintEvent(QPaintEvent* event) override
	{
		m_shapes.ForEach([&](const auto& shapeView) {
			shapeView->Draw(this);
			return true;
		});
	}

	void AddShape(const IShapeViewModelPtr& shapeViewModel, size_t pos)
	{
		const auto shape = ShapeViewFactory::CreateShape(m_parent, shapeViewModel);
		m_shapes.Insert(shape, pos);
		update();
	}

	void RemoveShape(const std::string& id)
	{
		m_shapes.Remove(id);
	}

private:
	Repository<IShapeView> m_shapes;
	IShapesViewModelPtr m_shapesViewModel;
	Frame m_frame{};
	QWidget* m_parent;
	ScopedConnection m_addShapesConnection;
	ScopedConnection m_removeShapesConnection;
	ScopedConnection m_selectedIdConnection;
	SelectionChangeSignal m_selectionChangeSignal;
};