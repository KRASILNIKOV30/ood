#pragma once
#include "IGroupShape.h"
#include <list>

class GroupShape final
	: public IGroupShape
	, public std::enable_shared_from_this<GroupShape>
{
public:
	void SetFrame(const Frame& frame) override;

	[[nodiscard]] Frame GetFrame() const override;
	ILineStyle& GetLineStyle() override;
	IFillStyle& GetFillStyle() override;
	void Draw(ICanvasPtr canvas) const override;
	IGroupShapePtr GetGroup() override;
	[[nodiscard]] size_t GetShapesCount() const override;
	IShape* GetShape(size_t index) override;
	void AddShape(IShape* shape) override;

private:
	std::list<IShapePtr> m_shapes;
};