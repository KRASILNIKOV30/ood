#ifndef SHAPES_H
#define SHAPES_H

#include "view/Painter.h"
#include "view/Selection.h"

#include <QMenuBar>
#include <QObject>
#include <QPainter>
#include <QToolBar>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <iostream>

QT_BEGIN_NAMESPACE

class Ui_PaintClass : public QObject
{
	Q_OBJECT
public:
	QPushButton* m_rectangle;
	QPushButton* m_triangle;
	QPushButton* m_circle;
	QToolBar* m_toolbar;
	QWidget* m_layout;
	std::shared_ptr<IPainter> m_painter;
	std::unique_ptr<Selection> m_selection;
	IShapeView* m_shapeView;

	void setupUi(QMainWindow* window, const IShapesViewModelPtr& model)
	{
		if (window->objectName().isEmpty())
			window->setObjectName(QString::fromUtf8("PaintClass"));
		window->resize(800, 600);

		m_toolbar = new QToolBar(window);
		m_toolbar->setMovable(false);

		m_rectangle = new QPushButton("Rectangle");
		m_triangle = new QPushButton("Triangle");
		m_circle = new QPushButton("Circle");

		m_toolbar->addWidget(m_rectangle);
		m_toolbar->addWidget(m_triangle);
		m_toolbar->addWidget(m_circle);

		window->addToolBar(m_toolbar);

		const auto menuBar = window->menuBar();
		menuBar->addAction("Open");
		menuBar->addAction("Save");
		menuBar->addAction("Save as");

		m_layout = new QWidget();
		m_layout->setMinimumSize(QSize(800, 600));
		m_layout->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

		m_painter = std::make_shared<Painter>(m_layout, model, m_rectangle, m_triangle, m_circle);
		m_selection = std::make_unique<Selection>(m_layout, m_painter.get());

		connect(m_rectangle, &QPushButton::clicked, this, [&]() { m_painter->AddShape("rectangle"); });

		window->setCentralWidget(m_layout);

		retranslateUi(window);
		QMetaObject::connectSlotsByName(window);
	}

	void retranslateUi(QMainWindow* PaintClass)
	{
		PaintClass->setWindowTitle(QCoreApplication::translate("PaintClass", "Paint", nullptr));
	}
};

namespace Ui
{
class PaintClass : public Ui_PaintClass
{
};
} // namespace Ui

QT_END_NAMESPACE

#endif // SHAPES_H
