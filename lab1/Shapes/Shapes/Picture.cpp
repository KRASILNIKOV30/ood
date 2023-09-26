#include "Picture.h"
#include "TriangleBehavior.h"
#include "CircleBehavior.h"
#include "LineBehavior.h"
#include "RectangleBehavior.h"
#include "TextBehavior.h"
#include "Common.h"

bool Picture::AddShape(std::string const& id, Color color, ShapeType type, std::unique_ptr<IShapeBehavior>&& shapeBehavior)
{
	if (!TryInsertShape(id, color, type, std::move(shapeBehavior)))
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

bool Picture::ChangeShape(std::string const& id, ShapeType type, std::unique_ptr<IShapeBehavior>&& shapeBehavior)
{
	if (!m_shapes.contains(id))
	{
		return false;
	}

	m_shapes[id]->SetDrawingStrategy(std::move(shapeBehavior));
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

bool Picture::TryInsertShape(std::string const& id, Color color, ShapeType type, std::unique_ptr<IShapeBehavior>&& shapeBehavior)
{
	return m_shapes.try_emplace(id, std::make_unique<Shape>(std::move(shapeBehavior), color)).second;
}

