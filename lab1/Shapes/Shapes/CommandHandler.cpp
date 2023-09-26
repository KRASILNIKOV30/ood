#include "CommandHandler.h"
#include <sstream>
#include "Common.h"
#include "CircleBehavior.h"
#include "TriangleBehavior.h"
#include "LineBehavior.h"
#include "TextBehavior.h"
#include "RectangleBehavior.h"

CommandHandler::CommandHandler(std::istream& input, std::ostream& output, Picture& picture, std::ostream& svgFile)
	: m_input(input)
	, m_output(output)
	, m_svgFile(svgFile)
	, m_picture(picture)
	, m_canvas(CCanvas(svgFile))
	, m_actionMap({
			{ "AddShape", bind(&CommandHandler::AddShape, this, std::placeholders::_1) },
			{ "MoveShape", bind(&CommandHandler::MoveShape, this, std::placeholders::_1) },
			{ "MovePicture", bind(&CommandHandler::MovePicture, this, std::placeholders::_1) },
			{ "DeleteShape", bind(&CommandHandler::DeleteShape, this, std::placeholders::_1) },
			{ "List", bind(&CommandHandler::ListShapes, this, std::placeholders::_1) },
			{ "ChangeColor", bind(&CommandHandler::ChangeColor, this, std::placeholders::_1) },
			{ "ChangeShape", bind(&CommandHandler::ChangeShape, this, std::placeholders::_1) },
			{ "DrawShape", bind(&CommandHandler::DrawShape, this, std::placeholders::_1) },
			{ "DrawPicture", bind(&CommandHandler::DrawPicture, this, std::placeholders::_1) },
		})
{
}

bool CommandHandler::HandleCommand()
{
	std::string command;
	m_input >> command;
	std::istringstream strm(command);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CommandHandler::AddShape(std::istream& args)
{
	std::string id;
	std::string colorStr;
	std::string typeStr;

	if (!(m_input >> id && m_input >> colorStr && m_input >> typeStr))
	{
		return false;
	}
	ShapeType type;
	auto optType = MakeShapeType(typeStr);
	if (!optType.has_value())
	{
		return false;
	}
	type = optType.value();

	Color color;
	StringToUint32(colorStr, color);

	auto optShape = MakeDrawingStrategy(type);
	if (!optShape.has_value())
	{
		return false;
	}

	m_picture.AddShape(id, color, type, std::move(optShape.value()));

	return true;
}

bool CommandHandler::MoveShape(std::istream& args)
{
	std::string id;
	double dx, dy;
	if (!(m_input >> id && m_input >> dx && m_input >> dy))
	{
		return false;
	}

	return m_picture.MoveShape(id, Point(dx, dy));
}

bool CommandHandler::MovePicture(std::istream& args)
{
	double dx, dy;
	if (!(m_input >> dx && m_input >> dy))
	{
		return false;
	}

	m_picture.MovePicture(Point(dx, dy));
	return true;
}

bool CommandHandler::DeleteShape(std::istream& args)
{
	std::string id;
	if (!(m_input >> id))
	{
		return false;
	}

	return m_picture.DeleteShape(id);
}

bool CommandHandler::ListShapes(std::istream& args) const
{
	std::cout << m_picture.ListShapes() << std::endl;
	return true;
}

bool CommandHandler::ChangeColor(std::istream& args)
{
	std::string id;
	std::string colorStr;
	if (!(m_input >> id && m_input >> colorStr))
	{
		return false;
	}
	Color color;
	StringToUint32(colorStr, color);

	m_picture.ChangeColor(id, color);
	return true;
}

bool CommandHandler::ChangeShape(std::istream& args)
{
	std::string id;
	std::string typeStr;

	if (!(m_input >> id && m_input >> typeStr))
	{
		return false;
	}
	ShapeType type;
	auto optType = MakeShapeType(typeStr);
	if (!optType.has_value())
	{
		return false;
	}
	type = optType.value();

	auto optShape = MakeDrawingStrategy(type);
	if (!optShape.has_value())
	{
		return false;
	}

	m_picture.ChangeShape(id, type, std::move(optShape.value()));

	return true;
}

bool CommandHandler::DrawShape(std::istream& args)
{
	std::string id;
	if (!(m_input >> id))
	{
		return false;
	}

	m_picture.DrawShape(id, m_canvas);

	return true;
}

bool CommandHandler::DrawPicture(std::istream& args)
{
	m_picture.DrawPicture(m_canvas);
	return true;
}

std::optional<ShapeType> CommandHandler::MakeShapeType(std::string type) const
{
	if (type == "circle")
	{
		return ShapeType::CIRCLE;
	}

	if (type == "triangle")
	{
		return ShapeType::TRIANGLE;
	}

	if (type == "line")
	{
		return ShapeType::LINE;
	}

	if (type == "rectangle")
	{
		return ShapeType::RECTANGLE;
	}

	if (type == "text")
	{
		return ShapeType::TEXT;
	}

	return std::nullopt;
}

std::optional<std::unique_ptr<IShapeBehavior>> CommandHandler::MakeDrawingStrategy(ShapeType type) const
{
	switch (type)
	{
	case ShapeType::CIRCLE:
	{
		double cx, cy, r;
		if (!(m_input >> cx && m_input >> cy && m_input >> r))
		{
			return std::nullopt;
		}
		return  std::make_unique<CircleBehavior>(Point{ cx, cy }, r);
	}
	case ShapeType::TRIANGLE:
	{
		double x1, y1, x2, y2, x3, y3;
		if (!(m_input >> x1 && m_input >> y1 && m_input >> x2 && m_input >> y2 && m_input >> x3 && m_input >> y3))
		{
			return std::nullopt;
		}
		return std::make_unique<TriangleBehavior>(Point{ x1, y1 }, Point{ x2, y2 }, Point{ x3, y3 });
	}
	case ShapeType::LINE:
	{
		double x1, y1, x2, y2;
		if (!(m_input >> x1 && m_input >> y1 && m_input >> x2 && m_input >> y2))
		{
			return std::nullopt;
		}
		return std::make_unique<LineBehavior>(Point{ x1, y1 }, Point{ x2, y2 });
	}
	case ShapeType::RECTANGLE:
	{
		double x1, y1, w, h;
		if (!(m_input >> x1 && m_input >> y1 && m_input >> w && m_input >> h))
		{
			return std::nullopt;
		}
		return std::make_unique<RectangleBehavior>(Point{ x1, y1 }, w, h);
	}
	case ShapeType::TEXT:
	{
		double x1, y1, s;
		std::string text;
		if (!(m_input >> x1 && m_input >> y1 && m_input >> s && std::getline(m_input, text)))
		{
			return std::nullopt;
		}
		return std::make_unique<TextBehavior>(Point{ x1, y1 }, s, text);
	}
	}
}
