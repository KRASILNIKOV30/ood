#pragma once

#include "IFlyBehavior.h"

class FlyCounter : public IFlyBehavior
{
public:
	void Fly()
	{
		m_flyCounter++;
	}

protected:
	int m_flyCounter = 0;
};