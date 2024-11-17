#pragma once
#include "../shapes/IShape.h"

class IGroupShape : public IShape
{
public:
	[[nodiscard]] virtual size_t GetShapesCount() const = 0;
	virtual IShape* GetShape(size_t index) = 0;
	virtual void AddShape(IShape* shape) = 0;
};