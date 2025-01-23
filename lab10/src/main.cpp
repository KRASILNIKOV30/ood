#include "appModel/ShapesAppModel.h"
#include "model/Shapes.h"
#include "ui_shapes.h"
#include "viewModel/ShapesViewModel.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QMainWindow window;
	Ui::PaintClass ui;

	const auto model = std::make_shared<Shapes>();
	const IShapesAppModelPtr appModel = std::make_shared<ShapesAppModel>(model.get());
	const IShapesViewModelPtr viewModel = std::make_shared<ShapesViewModel>(appModel);

	ui.setupUi(&window, viewModel);

	window.show();

	return QApplication::exec();
}