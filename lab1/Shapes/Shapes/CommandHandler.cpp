#include "CommandHandler.h"
#include <sstream>
#include "Common.h"
#include "CCanvas.h"

CommandHandler::CommandHandler(std::istream& input, std::ostream& output, Picture& picture, std::ostream& svgFile)
	: m_input(input)
	, m_output(output)
	, m_svgFile(svgFile)
	, m_picture(picture)
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

	std::vector<double> params;
	double x;
	
	m_input >> x;
	params.push_back(x);
	m_input >> x;
	params.push_back(x);
	m_input >> x;
	params.push_back(x);

	std::string text = "";
	//m_input >> text;

	ShapeType type;
	auto optType = MakeShapeType(typeStr);
	if (!optType.has_value())
	{
		return false;
	}
	type = optType.value();
	Color color;
	StringToUint32(colorStr, color);

	m_picture.AddShape(id, color, type, ShapeParameters{ params, text });

	return true;
}

bool CommandHandler::MoveShape(std::istream& args)
{
	return false;
}

bool CommandHandler::MovePicture(std::istream& args)
{
	return false;
}

bool CommandHandler::DeleteShape(std::istream& args)
{
	return false;
}

bool CommandHandler::ListShapes(std::istream& args) const
{
	return false;
}

bool CommandHandler::ChangeColor(std::istream& args)
{
	return false;
}

bool CommandHandler::ChangeShape(std::istream& args)
{
	return false;
}

bool CommandHandler::DrawShape(std::istream& args)
{
	CCanvas canvas(m_svgFile);

	std::string id;
	if (!(m_input >> id))
	{
		return false;
	}

	m_picture.DrawShape(id, canvas);

	return true;
}

bool CommandHandler::DrawPicture(std::istream& args)
{
	return false;
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
