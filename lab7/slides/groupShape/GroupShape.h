#pragma once
#include "IGroupShape.h"
#include "../styles/lineStyle/CompositeLineStyle.h"
#include "../styles/fillStyle/CompositeFillStyle.h"

#include <cassert>
#include <list>

class GroupShape final
	: public IGroupShape
	, public std::enable_shared_from_this<GroupShape>
{
public:
	GroupShape(const std::initializer_list<IShapePtr> shapes)
		: m_shapes(shapes)
	{}
	void SetFrame(const Frame& frame) override
	{
		// Получаем текущий фрейм группы
		const Frame currentFrame = GetFrame();

		// Вычисляем коэффициенты масштаба для X и Y
		double scaleX = frame.width / currentFrame.width;
		double scaleY = frame.height / currentFrame.height;

		// Сдвигаем группу, чтобы её левый верхний угол совпал с новым фреймом
		double deltaX = frame.leftTop.x - currentFrame.leftTop.x;
		double deltaY = frame.leftTop.y - currentFrame.leftTop.y;

		// Применяем изменения к каждой фигуре в группе
		for (auto& shape : m_shapes) {
			// Получаем текущий фрейм фигуры
			Frame shapeFrame = shape->GetFrame();

			// Вычисляем новые координаты и размеры фигуры с учетом масштаба и сдвига
			double newLeftTopX = frame.leftTop.x + (shapeFrame.leftTop.x - currentFrame.leftTop.x) * scaleX;
			double newLeftTopY = frame.leftTop.y + (shapeFrame.leftTop.y - currentFrame.leftTop.y) * scaleY;
			double newWidth = shapeFrame.width * scaleX;
			double newHeight = shapeFrame.height * scaleY;

			// Устанавливаем новый фрейм для фигуры
			shape->SetFrame({{newLeftTopX, newLeftTopY}, newWidth, newHeight});
		}
	}

	[[nodiscard]] Frame GetFrame() const override
	{
		assert(!m_shapes.empty());
		const auto& [leftTop, width, height] = m_shapes.front()->GetFrame();
		auto minY = leftTop.y;
		auto minX = leftTop.x;
		auto maxY = leftTop.y + height;
		auto maxX = leftTop.x + width;

		for (auto const& shape : m_shapes)
		{
			const auto& [leftTop, width, height] = shape->GetFrame();

			minY = std::min(minY, leftTop.y);
			minX = std::min(minX, leftTop.x);
			maxY = std::max(maxY, leftTop.y + height);
			maxX = std::max(maxX, leftTop.x + width);
		}

		return Frame{ minX, minY, maxX, maxY };
	}

	ILineStylePtr GetLineStyle() override
	{
		return std::make_shared<CompositeLineStyle>([this](const auto& cb) {
			for (auto const& shape : m_shapes)
			{
				if (!cb(shape->GetLineStyle()))
				{
					break;
				}
			}
		});
	}

	IFillStylePtr GetFillStyle() override
	{
		return std::make_shared<CompositeFillStyle>([this](const auto& cb) {
			for (auto const& shape : m_shapes)
			{
				if (!cb(shape->GetFillStyle()))
				{
					break;
				}
			}
		});
	}

	void Draw(const ICanvasPtr canvas) const override
	{
		for (auto const& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
	}

	IGroupShapePtr GetGroup() override
	{
		return shared_from_this();
	}

	[[nodiscard]] size_t GetShapesCount() const override
	{
		return m_shapes.size();
	}

	IShapePtr GetShape(size_t const index) override
	{
		if (index >= m_shapes.size())
		{
			throw std::out_of_range("GroupShape::GetShape index out of range");
		}

		return *std::next(m_shapes.begin(), index);
	}

	void AddShape(const IShapePtr& shape) override
	{
		m_shapes.push_back(shape);
	}

private:
	std::list<IShapePtr> m_shapes;
};