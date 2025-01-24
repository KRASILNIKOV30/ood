#pragma once
#include "../model/IShape.h"
#include <memory>
#include <string>

class IShapeAppModel
{
public:
	virtual void Reframe(Frame const& frame) = 0;
	virtual ScopedConnection DoOnReframe(ReframeSlot const& slot) = 0;

	[[nodiscard]] virtual std::string GetId() const = 0;
	[[nodiscard]] virtual Frame GetFrame() const = 0;
	[[nodiscard]] virtual std::string GetType() const = 0;

	virtual ~IShapeAppModel() = default;
};

using IShapeAppModelPtr = std::shared_ptr<IShapeAppModel>;
using IShapeAppModelConstPtr = const IShapeAppModelPtr;
