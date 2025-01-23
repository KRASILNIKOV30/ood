#include "ShapeView.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <iostream>
#include <qwidget.h>
#include <utility>

ShapeView::ShapeView(QWidget* parent, IShapeViewModelPtr shape)
	: QWidget(parent)
	, m_shape(std::move(shape))
{
}
void ShapeView::Draw(QWidget* parent)
{
	const QPainterPath path = GetPath();

	std::cout << "paintEvent" << std::endl;

	QPainter painter(parent);
	painter.setPen(Qt::NoPen);
	painter.fillPath(path, QBrush(Qt::black));
}

std::string ShapeView::GetId() const
{
	return m_shape->GetId();
}
Frame ShapeView::GetFrame()
{
	return m_shape->GetFrame();
}

void ShapeView::paintEvent(QPaintEvent* event)
{
	const QPainterPath path = GetPath();

	std::cout << "paintEvent" << std::endl;

	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.fillPath(path, QBrush(Qt::black));
}

void ShapeView::mousePressEvent(QMouseEvent* event)
{
	if (GetPath().contains(event->pos()))
	{
		m_shape->Click();
	}
	QWidget::mousePressEvent(event);
}

void ShapeView::mouseMoveEvent(QMouseEvent* event)
{
	QWidget::mouseMoveEvent(event);
}

void ShapeView::mouseReleaseEvent(QMouseEvent* event)
{
	QWidget::mouseReleaseEvent(event);
}
