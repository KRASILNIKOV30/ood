#include "ui_shapes.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QMainWindow window;
	Ui::PaintClass ui;
	ui.setupUi(&window);

	window.show();

	return QApplication::exec();
}