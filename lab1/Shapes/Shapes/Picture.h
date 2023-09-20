#pragma once
#include <map>
#include <string>
#include <memory>
#include "Shape.h"
#include "ShapeParameters.h"

class Picture
{
public: 
	bool AddShape(std::string const& id, Color color, ShapeType type, ShapeParameters const& params);
	bool MoveShape(std::string const& id, Point vector);
	void MovePicture(Point vector);
	bool DeleteShape(std::string const& id);
	std::string ListShapes() const;
	bool ChangeColor(std::string const& id, Color color);
	bool ChangeShape(std::string const& id, ShapeType type, ShapeParameters params);
	bool DrawShape(std::string const& id, ICanvas& canvas) const;
	void DrawPicture(ICanvas& canvas) const;

private:
	bool TryInsertShape(std::string const& id, Color color, ShapeType type, ShapeParameters const& params);
	std::unique_ptr<IDrawingStrategy> MakeDrawingStrategy(ShapeType type, ShapeParameters const& params);

private:
	using Shapes = std::map<std::string, std::unique_ptr<Shape>>;
	using ShapeIds = std::vector<std::string>;
	Shapes m_shapes;
	ShapeIds m_shapeIds;
};

