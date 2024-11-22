#pragma once
#include <iostream>
#include <memory>
#include <sstream>
#include "canvas/SvgCanvas.h"
#include "shapes/Rectangle.h"
#include "shapes/Triangle.h"
#include "shapes/Ellipse.h"
#include "groupShape/GroupShape.h"

using Color = uint32_t;

// Функция для рисования пейзажа с домиком
int main() {
	// Создаём дом
	std::shared_ptr<IShape> houseBase = std::make_shared<Rectangle>(Frame{{100, 300}, 400, 300}, 0x8B4513, 0x000000); // Коричневый дом
	std::shared_ptr<IShape> houseRoof = std::make_shared<Triangle>(Frame{{100, 200}, 400, 100}, 0xA52A2A, 0x000000); // Красная крыша

	// Создаём окна
	std::shared_ptr<IShape> window1 = std::make_shared<Ellipse>(Frame{{150, 350}, 50, 50}, 0xFFFFFF, 0x000000); // Белое окно 1
	std::shared_ptr<IShape> window2 = std::make_shared<Ellipse>(Frame{{350, 350}, 50, 50}, 0xFFFFFF, 0x000000); // Белое окно 2

	// Создаём дверь
	std::shared_ptr<IShape> door = std::make_shared<Rectangle>(Frame{{250, 450}, 100, 150}, 0xD2691E, 0x000000); // Коричневая дверь

	// Создаём группу для дома
	GroupShape houseGroup({ houseBase, houseRoof, window1, window2, door });

	// Создаём дерево
	std::shared_ptr<IShape> treeTrunk = std::make_shared<Rectangle>(Frame{{550, 400}, 40, 100}, 0x8B4513, 0x000000); // Ствол дерева
	std::shared_ptr<IShape> treeLeaves = std::make_shared<Ellipse>(Frame{{570, 350}, 100, 100}, 0x228B22, 0x000000); // Листья дерева

	// Создаём группу для дерева
	GroupShape treeGroup({ treeTrunk, treeLeaves });

	// Создаём холст для рисования
	std::stringstream ss;
	std::shared_ptr<ICanvas> canvas = std::make_shared<SvgCanvas>(ss);

	// Рисуем домик
	houseGroup.Draw(canvas);

	// Рисуем дерево
	treeGroup.Draw(canvas);

	// Выводим результат на экран
	std::cout << ss.str() << std::endl;

	return 0;
}
