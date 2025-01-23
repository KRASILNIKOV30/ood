#pragma once
#include "../../Frame.h"
#include "../ShapeView.h"
#include <QPainterPath>
#include <QPoint>
#include <QWidget>

class RectangleView final : public ShapeView
{
public:
	RectangleView(QWidget* parent, const IShapeViewModelPtr& shape)
		: ShapeView(parent, shape)
	{
		const auto [position, size] = shape->GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		m_topLeft = QPoint(x, y);
		m_bottomRight = QPoint(x + width, y + height);

		// setFixedSize(width, height);
		// setMask(GetRegion());
	}

protected:
	[[nodiscard]] QPainterPath GetPath() const override
	{
		QPainterPath path;
		path.addRect(QRect(m_topLeft, m_bottomRight));
		return path;
	}

	[[nodiscard]] QRegion GetRegion() const
	{
		return QRect(m_topLeft, m_bottomRight);
	}

private:
	QPoint m_topLeft;
	QPoint m_bottomRight;
};
