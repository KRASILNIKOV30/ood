#pragma once
#include <sstream>

#include "CEllipse.h"
#include "CRectangle.h"
#include "CTrinagle.h"
#include "IShapeFactory.h"

class CShapeFactory final : public IShapeFactory
{
public:
	std::unique_ptr<CShape> CreateShape(std::string const& descr) override
	{
		std::stringstream ss(descr);
		std::string type, color;
		ss >> type;
		switch (type)
		{
		case "rectangle":
		{
			double x, y, w, h;
			if (!(ss >> x && ss >> y && ss >> w && ss >> h && ss >> color))
			{
				throw std::exception("Incorrect parameters");
			}
			return std::make_unique<CRectangle>(Point{ x, y }, w, h, StrToColor(color));
		}
		case "triangle":
		{
			double x1, y1, x2, y2, x3, y3;
			if (!(ss >> x1 && ss >> y1 && ss >> x2 && ss >> y2 && ss >> x3 && ss >> y3 && ss >> color))
			{
				throw std::exception("Incorrect parameters");
			}
			return std::make_unique<CTriangle>(Point{ x1, y1 }, Point{ x2, y2 }, Point{ x3, y3 }, StrToColor(color));
		}
		case "ellipse":
		{
			double x, y, w, h;
			if (!(ss >> x && ss >> y && ss >> w && ss >> h && ss >> color))
			{
				throw std::exception("Incorrect parameters");
			}
			return std::make_unique<CEllipse>(Point{ x, y }, w, h, StrToColor(color));
		}
		default: throw std::exception("Unknown shape");
		}
	}
};
