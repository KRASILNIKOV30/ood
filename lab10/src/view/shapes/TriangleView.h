#pragma once
#include "../../Frame.h"
#include "../ShapeView.h"
#include <QPainterPath>
#include <QPoint>
#include <QPolygon>
#include <QWidget>

class TriangleView final : public ShapeView
{
public:
	TriangleView(QWidget* parent, const IShapeViewModelPtr& shape)
		: ShapeView(parent, shape)
	{
		const auto [position, size] = shape->GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		m_points.append(QPoint(x, y + height));
		m_points.append(QPoint(x + width / 2, y));
		m_points.append(QPoint(x + width, y + height));

		setFixedSize(width, height);
		setMask(GetRegion());
	}

private:
	[[nodiscard]] QPainterPath GetPath() const override
	{
		QPainterPath path;
		path.moveTo(m_points[0]);
		path.lineTo(m_points[1]);
		path.lineTo(m_points[2]);
		path.lineTo(m_points[0]);

		return path;
	}

	[[nodiscard]] QRegion GetRegion() const
	{
		return QPolygon(m_points);
	}

private:
	QVector<QPoint> m_points;
};