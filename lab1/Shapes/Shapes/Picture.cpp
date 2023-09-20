#include "Picture.h"
#include "TriangleDrawingStrategy.h"
#include "CircleDrawingStrategy.h"
#include "LineDrawingStrategy.h"
#include "RectangleDrawingStrategy.h"
#include "TextDrawingStrategy.h"
#include "Common.h"

bool Picture::AddShape(std::string const& id, Color color, ShapeType type, ShapeParameters const& params)
{
	if (!TryInsertShape(id, color, type, params))
	{
		return false;
	}

	m_shapeIds.push_back(id);
	return true;
}

bool Picture::MoveShape(std::string const& id, Point vector)
{
	if (!m_shapes.contains(id))
	{
		return false;
	}

	m_shapes[id]->Move(vector);
	return true;
}

void Picture::MovePicture(Point vector)
{
	for (auto& id : m_shapeIds)
	{
		MoveShape(id, vector);
	}
}

bool Picture::DeleteShape(std::string const& id)
{
	if (!m_shapes.contains(id))
	{
		return false;
	}

	std::erase(m_shapeIds, id);
	std::erase_if(m_shapes, [id](auto const& item) { return item.first == id; });
	return true;
}

std::string Picture::ListShapes() const
{
	std::stringstream result;
	int i = 1;
	for (auto& id : m_shapeIds)
	{
		result << i << ". " << m_shapes.at(id)->GetType() << " " << id << " #" << GetHexStrFromUint32(m_shapes.at(id)->GetColor(), COLOR_LEN);
		for (auto& param : m_shapes.at(id)->GetParams().layoutParams)
		{
			result << " " << param;
		}
		if (!m_shapes.at(id)->GetParams().text.empty())
		{
			result << " " << m_shapes.at(id)->GetParams().text;
		}
		result << std::endl;
		i++;
	}

	return result.str();
}

bool Picture::ChangeColor(std::string const& id, Color color)
{
	if (!m_shapes.contains(id))
	{
		return false;
	}

	m_shapes[id]->SetColor(color);
	return true;
}

bool Picture::ChangeShape(std::string const& id, ShapeType type, ShapeParameters params)
{
	if (!m_shapes.contains(id))
	{
		return false;
	}

	m_shapes[id]->SetDrawingStrategy(MakeDrawingStrategy(type, params));
	return true;
}

bool Picture::DrawShape(std::string const& id, ICanvas& canvas) const
{
	if (!m_shapes.contains(id))
	{
		return false;
	}

	m_shapes.at(id)->Draw(canvas);
	return true;
}

void Picture::DrawPicture(ICanvas& canvas) const
{
	for (auto& id : m_shapeIds)
	{
		DrawShape(id, canvas);
	}
}

bool Picture::TryInsertShape(std::string const& id, Color color, ShapeType type, ShapeParameters const& params)
{
	return m_shapes.try_emplace(id, std::make_unique<Shape>(MakeDrawingStrategy(type, params))).second;
}

std::unique_ptr<IDrawingStrategy> Picture::MakeDrawingStrategy(ShapeType type, ShapeParameters const& params)
{
	switch (type)
	{
	case ShapeType::CIRCLE:
		return  std::make_unique<CircleDrawingStrategy>
			(
				Point{ params.layoutParams[0], params.layoutParams[1] },
				params.layoutParams[2]
			);

	case ShapeType::TRIANGLE:
		return std::make_unique<TriangleDrawingStrategy>
			(
				Point{ params.layoutParams[0], params.layoutParams[1] },
				Point{ params.layoutParams[2], params.layoutParams[3] },
				Point{ params.layoutParams[4], params.layoutParams[5] }
			);

	case ShapeType::LINE:
		return std::make_unique<LineDrawingStrategy>
			(
				Point{ params.layoutParams[0], params.layoutParams[1] },
				Point{ params.layoutParams[2], params.layoutParams[3] }
			);

	case ShapeType::RECTANGLE:
		return std::make_unique<RectangleDrawingStrategy>
			(
				Point{ params.layoutParams[0], params.layoutParams[1] },
				params.layoutParams[2],
				params.layoutParams[3]
			);

	case ShapeType::TEXT:
		return std::make_unique<TextDrawingStrategy>
			(
				Point{ params.layoutParams[0], params.layoutParams[1] },
				params.layoutParams[2],
				params.text
			);
	}
}
