#pragma once
#include <memory>
#include <string>
#include "CShape.h"

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;
	virtual std::unique_ptr<CShape> CreateShape(std::string const& descr) = 0;
};
