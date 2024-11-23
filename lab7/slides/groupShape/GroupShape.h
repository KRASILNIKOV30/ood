#pragma once
#include "IGroupShape.h"
#include "../styles/lineStyle/CompositeLineStyle.h"
#include "../styles/fillStyle/CompositeFillStyle.h"
#include <cassert>
#include <vector>

class GroupShape final
	: public IGroupShape
	, public std::enable_shared_from_this<GroupShape>
{
public:
	//передавать вектор или 2 итератора (исправлено)
	// Добавить удаление
	// ReSharper disable once CppNonExplicitConvertingConstructor
	GroupShape(std::vector<IShapePtr> shapes)
		: m_shapes(std::move(shapes))
	{
		// Лучше хранить в векторе
		if (m_shapes.empty())
		{
			throw std::logic_error("GroupShape cannot be empty");
		}
	}
	void SetFrame(const Frame& frame) override
	{
		const auto [leftTop, width, height] = GetFrame();

		const double scaleX = frame.width / width;
		const double scaleY = frame.height / height;

		for (const auto& shape : m_shapes)
		{
			Frame shapeFrame = shape->GetFrame();

			const double newLeftTopX = frame.leftTop.x + (shapeFrame.leftTop.x - leftTop.x) * scaleX;
			const double newLeftTopY = frame.leftTop.y + (shapeFrame.leftTop.y - leftTop.y) * scaleY;
			const double newWidth = shapeFrame.width * scaleX;
			const double newHeight = shapeFrame.height * scaleY;

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

	// Можно не создавать каждый раз (исправлено)
	ILineStyle& GetLineStyle() override
	{
		if (!m_lineStyle.has_value())
		{
			m_lineStyle = CompositeLineStyle([this](const auto& cb) {
				for (auto const& shape : m_shapes)
				{
					if (!cb(shape->GetLineStyle()))
					{
						break;
					}
				}
			});
		}

		return m_lineStyle.value();
	}

	IFillStyle& GetFillStyle() override
	{
		if (!m_fillStyle.has_value())
		{
			m_fillStyle = CompositeFillStyle([this](const auto& cb) {
				for (auto const& shape : m_shapes)
				{
					if (!cb(shape->GetFillStyle()))
					{
						break;
					}
				}
			});
		}

		return m_fillStyle.value();
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

		return m_shapes[index];
	}

	void AddShape(const IShapePtr& shape) override
	{
		m_shapes.push_back(shape);
	}

private:
	std::vector<IShapePtr> m_shapes;
	std::optional<CompositeFillStyle> m_fillStyle;
	std::optional<CompositeLineStyle> m_lineStyle;
};