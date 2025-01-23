#pragma once
#include "../viewModel/IShapeViewModel.h"
#include "IShapeView.h"
#include <qwidget.h>

class ShapeView
	: public QWidget
	, public IShapeView
{
	Q_OBJECT

public:
	ShapeView(QWidget* parent, IShapeViewModelPtr shape);
	void Draw(QWidget* parent) override;
	[[nodiscard]] std::string GetId() const override;
	Frame GetFrame() override;
	[[nodiscard]] virtual QPainterPath GetPath() const = 0;

private:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) final;
	void mouseMoveEvent(QMouseEvent* event) final;
	void mouseReleaseEvent(QMouseEvent* event) final;

private:
	IShapeViewModelPtr m_shape;
};
