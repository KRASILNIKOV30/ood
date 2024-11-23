#include <memory>
#include "canvas/SvgCanvas.h"
#include "shapes/Rectangle.h"
#include "shapes/Triangle.h"
#include "shapes/Ellipse.h"
#include "groupShape/GroupShape.h"

#include <fstream>

using Color = uint32_t;

int main() {
	const auto houseBase = std::make_shared<Rectangle>(Frame{{100, 300}, 400, 300}, 0x8B4513, 0x000000);
	const auto houseRoof = std::make_shared<Triangle>(Frame{{100, 200}, 400, 100}, 0xA52A2A, 0x000000);

	const auto window1 = std::make_shared<Ellipse>(Frame{{175, 350}, 50, 50}, 0x69a8f5, 0x000000);
	const auto window2 = std::make_shared<Ellipse>(Frame{{375, 350}, 50, 50}, 0x69a8f5, 0x000000);

	const auto door = std::make_shared<Rectangle>(Frame{{250, 450}, 100, 150}, 0xD2691E, 0x000000);

	GroupShape houseGroup({ houseBase, houseRoof, window1, window2, door });

	const auto treeTrunk = std::make_shared<Rectangle>(Frame{{600, 400}, 40, 100}, 0x8B4513, 0x000000);
	const auto treeLeaves = std::make_shared<Ellipse>(Frame{{570, 350}, 100, 100}, 0x228B22, 0x000000);

	GroupShape treeGroup({ treeTrunk, treeLeaves });

	std::ofstream svgFile("slides.svg");
	const auto canvas = std::make_shared<SvgCanvas>(svgFile);

	houseGroup.Draw(canvas);
	treeGroup.Draw(canvas);

	return 0;
}
