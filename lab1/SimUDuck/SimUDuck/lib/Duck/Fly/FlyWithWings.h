#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include "FlyCounter.h"

class FlyWithWings : public FlyCounter 
{
public:
	void Fly()
	{
		FlyCounter::Fly();
		std::cout << m_flyCounter << ": I'm flying with wings!!" << std::endl;
	}
};

#endif
