#ifndef SHAPES_H
#define SHAPES_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QToolBar>
#include <QMenuBar>

QT_BEGIN_NAMESPACE

class Ui_PaintClass
{
public:
    QPushButton *m_rectangle;
    QPushButton *m_triangle;
    QPushButton *m_circle;
	QToolBar *m_toolbar;

    void setupUi(QMainWindow *window)
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

        retranslateUi(window);
        QMetaObject::connectSlotsByName(window);
    } // setupUi

    void retranslateUi(QMainWindow *PaintClass)
    {
        PaintClass->setWindowTitle(QCoreApplication::translate("PaintClass", "Paint", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PaintClass: public Ui_PaintClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SHAPES_H
