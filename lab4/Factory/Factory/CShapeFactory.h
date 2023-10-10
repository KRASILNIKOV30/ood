#pragma once
#include <sstream>

#include "CEllipse.h"
#include "CRectangle.h"
#include "CRegularPolygon.h"
#include "CTriangle.h"
#include "IShapeFactory.h"
//Разобраться с теорией
//Разобраться в том, что делает абстрактная фабрика
class CShapeFactory final : public IShapeFactory
{
public:
	//Уменьшить метод
	// Не выбрасывать базовое исключение
	std::shared_ptr<CShape> CreateShape(std::string const& descr) const override
	{
		std::stringstream ss(descr);
		std::string type, color;
		ss >> type;
		if (type == "rectangle")
		{
			double x, y, w, h;
			if (!(ss >> x && ss >> y && ss >> w && ss >> h && ss >> color))
			{
				throw std::exception("Incorrect parameters");
			}
			return std::make_shared<CRectangle>(Point{ x, y }, w, h, StrToColor(color));
		}
		if (type == "triangle")
		{
			double x1, y1, x2, y2, x3, y3;
			if (!(ss >> x1 && ss >> y1 && ss >> x2 && ss >> y2 && ss >> x3 && ss >> y3 && ss >> color))
			{
				throw std::exception("Incorrect parameters");
			}
			return std::make_shared<CTriangle>(Point{ x1, y1 }, Point{ x2, y2 }, Point{ x3, y3 }, StrToColor(color));
		}
		if (type == "ellipse")
		{
			double x, y, w, h;
			if (!(ss >> x && ss >> y && ss >> w && ss >> h && ss >> color))
			{
				throw std::exception("Incorrect parameters");
			}
			return std::make_shared<CEllipse>(Point{ x, y }, w, h, StrToColor(color));
		}
		if (type == "polygon")
		{
			int i;
			double x, y, r;
			if (!(ss >> x && ss >> y && ss >> r && ss >> i && ss >> color))
			{
				throw std::exception("Incorrect parameters");
			}
			return std::make_shared<CRegularPolygon>(Point{ x, y }, r, i, StrToColor(color));
		}
		throw std::exception("Unknown shape");
	}
};
