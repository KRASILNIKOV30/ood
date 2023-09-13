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
		//Сделать отдельные стратегии (Исправлено)
		FlyStrategy flyBehavior,
		QuackStrategy quackBehavior,
		DanceStrategy danceBehavior
	)
		: m_quackBehavior(std::move(quackBehavior))
		, m_danceBehavior(std::move(danceBehavior))
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		//Добавить assert (Исправлено)
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
		m_flyBehavior();
	}

	void Dance()
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
	QuackStrategy m_quackBehavior;
	DanceStrategy m_danceBehavior;
};

#endif
