#pragma once
#include <iostream>
#include <functional>
#include <map>
#include "../../../../vcpkg/installed/x64-windows/include/SDL2/SDL_video.h"
#include "Picture.h"
#include "ShapeParameters.h"
#include <optional>
#include "CCanvas.h"

class CommandHandler
{
public:
	CommandHandler(std::istream& input, std::ostream& output, Picture& picture, std::ostream& svgFile);
	bool HandleCommand();

private:
	bool AddShape(std::istream& args);
	bool MoveShape(std::istream& args);
	bool MovePicture(std::istream& args);
	bool DeleteShape(std::istream& args);
	bool ListShapes(std::istream& args) const;
	bool ChangeColor(std::istream& args);
	bool ChangeShape(std::istream& args);
	bool DrawShape(std::istream& args);
	bool DrawPicture(std::istream& args);
	std::optional<ShapeType> MakeShapeType(std::string type) const;
	std::optional<std::unique_ptr<IShapeBehavior>> MakeDrawingStrategy(ShapeType type) const;


private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
	std::ostream& m_svgFile;
	Picture& m_picture;
	CCanvas m_canvas;
};

