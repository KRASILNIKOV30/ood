#pragma once
#include "../Frame.h"
#include "../canvas/ICanvas.h"
#include "../styles/fillStyle/IFillStyle.h"
#include "../styles/lineStyle/ILineStyle.h"

class IGroupShape;
using IGroupShapePtr = std::shared_ptr<IGroupShape>;

class IShape
{
public:
	virtual void SetFrame(Frame const& frame) = 0;
	[[nodiscard]] virtual Frame GetFrame() const = 0;
	virtual ILineStylePtr GetLineStyle() = 0;
	virtual IFillStylePtr GetFillStyle() = 0;
	virtual void Draw(ICanvasPtr canvas) const = 0;
	virtual IGroupShapePtr GetGroup() = 0;

	virtual ~IShape() = 0;
};

using IShapePtr = std::shared_ptr<IShape>;
