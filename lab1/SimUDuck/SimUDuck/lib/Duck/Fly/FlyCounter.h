#pragma once

#include "IFlyBehavior.h"

class FlyCounter : public IFlyBehavior
{
public:
	void Fly()
	{
		m_flyCounter++;
	}

	int GetFlyCounter() const
	{
		return m_flyCounter;
	}

private:
	int m_flyCounter = 0;
};