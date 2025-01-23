#pragma once
#include "../../Frame.h"
#include "../ShapeView.h"
#include <QPainterPath>
#include <QWidget>

class EllipseView final : public ShapeView
{
public:
	EllipseView(QWidget* parent, const IShapeViewModelPtr& shape)
		: ShapeView(parent, shape)
	{
		const auto [position, size] = shape->GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		m_rect = QRect(x, y, width, height);

		QWidget::setFixedSize(width, height);
		QWidget::setMask(GetRegion());
	}

	[[nodiscard]] QPainterPath GetPath() const override
	{
		QPainterPath path;
		path.addEllipse(m_rect);
		return path;
	}

protected:
	[[nodiscard]] QRegion GetRegion() const
	{
		return { m_rect, QRegion::Ellipse };
	}

private:
	QRect m_rect;
};
