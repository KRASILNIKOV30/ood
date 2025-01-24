#pragma once
#include <memory>
#include <string>

class ICanvas
{
public:
	virtual void AddShape(std::string const& type) = 0;

	virtual ~ICanvas() = default;
};

using ICanvasPtr = std::shared_ptr<ICanvas>;
