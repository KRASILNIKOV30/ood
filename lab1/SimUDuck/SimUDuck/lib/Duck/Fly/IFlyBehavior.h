#ifndef LAB01_SIMUDUCK_IFLYBEHAVIOR_H
#define LAB01_SIMUDUCK_IFLYBEHAVIOR_H

class IFlyBehavior
{
public:
	virtual ~IFlyBehavior(){};
	virtual void Fly() = 0;
};

#endif
