#pragma once
#include "IDanceBehavior.h"

class DancingWaltz : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dancing a waltz" << std::endl;
	}
};