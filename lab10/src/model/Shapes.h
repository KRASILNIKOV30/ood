#pragma once
#include "IShapes.h"

#include <list>
#include <unordered_map>

class Shapes final : public IShapes
{
public:
	void AddShape(IShapePtr&& shape) override;
	void RemoveShape(std::string const& id) override;
	[[nodiscard]] const IShape* GetShape(std::string const& id) const override;
	void ForEach(std::function<bool(const IShape*)> callback) const override;

private:
	using OrderedShapes = std::list<IShapePtr>;
	using ShapeMap = std::unordered_map<std::string, OrderedShapes::iterator>;

	OrderedShapes m_shapes;
	ShapeMap m_shapesMap;
};