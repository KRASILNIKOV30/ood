#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include "FlyCounter.h"

class FlyWithWings : public IFlyBehavior 
{
public:
	void Fly()
	{
		std::cout << ++m_flyCounter << ": I'm flying with wings!!" << std::endl;
	}

private:
	int m_flyCounter = 0;
};

#endif
