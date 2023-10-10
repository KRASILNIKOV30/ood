#pragma once
#include <memory>
#include <string>
#include "CShape.h"
//�������� ����������� ������
class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;
	virtual std::shared_ptr<CShape> CreateShape(std::string const& descr) const = 0;
};
