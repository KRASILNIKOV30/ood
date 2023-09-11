#pragma once

#include "IDanceBehavior.h"

class DancingMinuet : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dancing a minuet" << std::endl;
	}
};