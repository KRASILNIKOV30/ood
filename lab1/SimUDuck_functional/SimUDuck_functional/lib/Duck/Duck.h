#ifndef DUCK_H
#define DUCK_H

#include "../../Strategy.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

class Duck
{
public:
	Duck
	(
		FlyStrategy&& flyBehavior,
		Strategy&& quackBehavior,
		Strategy&& danceBehavior
	)
		: m_quackBehavior(std::move(quackBehavior))
		, m_danceBehavior(std::move(danceBehavior))
	{
		assert(m_quackBehavior);
		SetFlyBehavior(std::move(flyBehavior));
	}

	void Quack() const
	{
		m_quackBehavior();
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
		m_flyBehavior(m_flycounter);
	}

	virtual void Dance()
	{
		m_danceBehavior();
	}

	void SetFlyBehavior(FlyStrategy&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = std::move(flyBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyStrategy m_flyBehavior;
	Strategy m_quackBehavior;
	Strategy m_danceBehavior;
	int m_flycounter = 0;
};

#endif
