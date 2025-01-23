#pragma once
#include "Painter.h"
#include <QBrush>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QSizeF>
#include <qpen.h>

class Selection final : public QWidget
{
	Q_OBJECT

public:
	Selection(QWidget* parent, IPainterPtr const& painter)
		: QWidget(parent)
	{
		setMouseTracking(true);
		setAttribute(Qt::WA_OpaquePaintEvent);
		m_draggedCorner = None;

		m_selectionConnection = painter->DoOnSelectionChange([&]() {
			const auto shape = painter->GetSelectedShape();
			SetFrame(shape);
		});
	}

private:
	enum Corner
	{
		None,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	enum Edge
	{
		NoEdge,
		Top,
		Right,
		Bottom,
		Left
	};

	void SetFrame(const std::optional<IShapeViewPtr>& shapeView)
	{
		if (!shapeView.has_value())
		{
			m_frame.reset();
		}
		else
		{
			const auto [position, size] = shapeView.value()->GetFrame();
			const auto [x, y] = position;
			const auto [width, height] = size;
			m_frame = { x, y, width, height };
		}

		update();
	}

	void paintEvent(QPaintEvent* event) override
	{
		if (!m_frame.has_value())
		{
			return QWidget::paintEvent(event);
		}
		const auto frame = m_frame.value();

		QPainter painter(this);
		painter.setPen(QPen(Qt::DashLine));
		painter.setBrush(Qt::transparent);

		painter.drawRect(frame);

		const QPoint leftTop = frame.topLeft();
		const QPoint rightTop = frame.topRight();
		const QPoint rightBottom = frame.bottomRight();
		const QPoint leftBottom = frame.bottomLeft();

		painter.setBrush(QBrush(Qt::black));
		painter.drawRect(leftTop.x() - 5, leftTop.y() - 5, 10, 10);
		painter.drawRect(rightTop.x() + 5, rightTop.y() - 5, 10, 10);
		painter.drawRect(rightBottom.x() + 5, rightBottom.y() + 5, 10, 10);
		painter.drawRect(leftBottom.x() - 5, leftBottom.y() + 5, 10, 10);

		painter.setBrush(Qt::transparent);
		painter.setPen(QPen(Qt::DashLine));
		painter.drawLine(leftTop, rightTop);
		painter.drawLine(rightTop, rightBottom);
		painter.drawLine(rightBottom, leftBottom);
		painter.drawLine(leftBottom, leftTop);
	}

	void mousePressEvent(QMouseEvent* event) override
	{
		if (IsCornerClicked(event->pos()))
		{
			m_draggedCorner = GetCornerByClick(event->pos());
		}
		else if (IsEdgeClicked(event->pos()))
		{
			m_draggedEdge = GetEdgeByClick(event->pos());
		}
	}

	void mouseMoveEvent(QMouseEvent* event) override
	{
		if (m_draggedCorner != None)
		{
			// MoveCorner(event->pos());
		}
		else if (m_draggedEdge != NoEdge)
		{
			// MoveEdge(event->pos());
		}
	}

	void mouseReleaseEvent(QMouseEvent* event) override
	{
		m_draggedCorner = None;
		m_draggedEdge = NoEdge;
	}

	[[nodiscard]] bool IsCornerClicked(const QPoint& point) const
	{
		if (!m_frame.has_value())
		{
			return false;
		}
		const auto frame = m_frame.value();
		return (QRect(
					frame.topLeft() - QPoint(5, 5), QSize(10, 10))
					.contains(point)
			|| QRect(frame.topRight() - QPoint(5, 5), QSize(10, 10)).contains(point)
			|| QRect(frame.bottomLeft() - QPoint(5, 5), QSize(10, 10)).contains(point)
			|| QRect(frame.bottomRight() - QPoint(5, 5), QSize(10, 10)).contains(point));
	}

	[[nodiscard]] bool IsEdgeClicked(const QPoint& point) const
	{
		if (!m_frame.has_value())
		{
			return false;
		}
		const auto frame = m_frame.value();
		const QRect topEdge(frame.topLeft(), QSize(frame.width(), 10));
		const QRect rightEdge(frame.topRight(), QSize(10, frame.height()));
		const QRect bottomEdge(frame.bottomLeft() - QPoint(0, 10), QSize(frame.width(), 10));
		const QRect leftEdge(frame.topLeft() - QPoint(10, 0), QSize(10, frame.height()));

		return topEdge.contains(point) || rightEdge.contains(point) || bottomEdge.contains(point) || leftEdge.contains(point);
	}

	[[nodiscard]] Corner GetCornerByClick(const QPoint& point) const
	{
		if (!m_frame.has_value())
		{
			return None;
		}
		const auto frame = m_frame.value();

		if (QRect(frame.topLeft() - QPoint(5, 5), QSize(10, 10)).contains(point))
		{
			return TopLeft;
		}
		if (QRect(frame.topRight() - QPoint(5, 5), QSize(10, 10)).contains(point))
		{
			return TopRight;
		}
		if (QRect(frame.bottomLeft() - QPoint(5, 5), QSize(10, 10)).contains(point))
		{
			return BottomLeft;
		}
		if (QRect(frame.bottomRight() - QPoint(5, 5), QSize(10, 10)).contains(point))
		{
			return BottomRight;
		}

		return None;
	}

	[[nodiscard]] Edge GetEdgeByClick(const QPoint& point) const
	{
		if (!m_frame.has_value())
		{
			return NoEdge;
		}
		const auto frame = m_frame.value();

		const QRect topEdge(frame.topLeft(), QSize(frame.width(), 10));
		const QRect rightEdge(frame.topRight(), QSize(10, frame.height()));
		const QRect bottomEdge(frame.bottomLeft() - QPoint(0, 10), QSize(frame.width(), 10));
		const QRect leftEdge(frame.topLeft() - QPoint(10, 0), QSize(10, frame.height()));

		if (topEdge.contains(point))
			return Top;
		if (rightEdge.contains(point))
			return Right;
		if (bottomEdge.contains(point))
			return Bottom;
		if (leftEdge.contains(point))
			return Left;

		return NoEdge;
	}

private:
	std::optional<QRect> m_frame;
	Corner m_draggedCorner = None;
	Edge m_draggedEdge = NoEdge;
	ScopedConnection m_selectionConnection;
};
