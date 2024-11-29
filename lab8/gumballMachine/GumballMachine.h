#pragma once
#include <format>
#include <iostream>

namespace with_state
{

struct IState
{
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual void Refill(unsigned ballsNum) = 0;
	[[nodiscard]] virtual std::string ToString() const = 0;
	virtual ~IState() = default;
};

struct IGumballMachine
{
	virtual void ReleaseBall() = 0;
	[[nodiscard]] virtual unsigned GetBallCount() const = 0;
	virtual void SetCoins(unsigned count) = 0;
	[[nodiscard]] virtual unsigned GetCoinCount() const = 0;
	virtual void SetBalls(unsigned ballsNum) = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};

class SoldState final : public IState
{
public:
	SoldState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}
	void InsertQuarter() override
	{
		std::cout << "Please wait, we're already giving you a gumball" << std::endl;
	}
	void EjectQuarter() override
	{
		std::cout << "Sorry you already turned the crank" << std::endl;
	}
	void TurnCrank() override
	{
		std::cout << "Turning twice doesn't get you another gumball" << std::endl;
	}
	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		m_gumballMachine.SetCoins(m_gumballMachine.GetCoinCount() - 1);
		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs" << std::endl;
			m_gumballMachine.SetSoldOutState();
		}
		else
		{
			if (m_gumballMachine.GetCoinCount() > 0)
			{
				m_gumballMachine.SetHasQuarterState();
				return;
			}
			m_gumballMachine.SetNoQuarterState();
		}
	}
	[[nodiscard]] std::string ToString() const override
	{
		return "delivering a gumball";
	}
	void Refill(unsigned const ballsNum) override
	{
		std::cout << "Can not refill during giving a gumball" << std::endl;
	}

private:
	IGumballMachine& m_gumballMachine;
};

class SoldOutState final : public IState
{
public:
	SoldOutState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out" << std::endl;
	}
	void EjectQuarter() override
	{
		if (m_gumballMachine.GetCoinCount() == 0)
		{
			std::cout << "You can't eject, you haven't inserted a quarter yet" << std::endl;
			return;
		}
		std::cout << "Quarter returned" << std::endl;
		m_gumballMachine.SetCoins(0);
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs" << std::endl;
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed" << std::endl;
	}
	std::string ToString() const override
	{
		return "sold out";
	}
	void Refill(unsigned const ballsNum) override
	{
	}

private:
	IGumballMachine& m_gumballMachine;
};

class HasQuarterState final : public IState
{
public:
	HasQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		if (m_gumballMachine.GetCoinCount() >= 5)
		{
			std::cout << "You can't insert another quarter" << std::endl;
			return;
		}

		m_gumballMachine.SetCoins(m_gumballMachine.GetCoinCount() + 1);
		std::cout << "You inserted a quarter" << std::endl;
	}
	void EjectQuarter() override
	{
		std::cout << "Quarter returned" << std::endl;
		m_gumballMachine.SetCoins(0);
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned..." << std::endl;
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed" << std::endl;
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}
	void Refill(unsigned const ballsNum) override
	{
	}

private:
	IGumballMachine& m_gumballMachine;
};

class NoQuarterState final : public IState
{
public:
	NoQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{
	}

	void InsertQuarter() override
	{
		std::cout << "You inserted a quarter" << std::endl;
		m_gumballMachine.SetCoins(m_gumballMachine.GetCoinCount() + 1);
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter" << std::endl;
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter" << std::endl;
	}
	void Dispense() override
	{
		std::cout << "You need to pay first" << std::endl;
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}
	void Refill(unsigned const ballsNum) override
	{
		m_gumballMachine.SetBalls(ballsNum);
	}

private:
	IGumballMachine& m_gumballMachine;
};

class GumballMachine : private IGumballMachine
{
public:
	GumballMachine(const unsigned numBalls)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_count(numBalls)
	{
		if (m_count > 0)
		{
			m_state = &m_noQuarterState;
		}
	}
	void EjectQuarter()
	{
		m_state->EjectQuarter();
	}
	void InsertQuarter()
	{
		m_state->InsertQuarter();
	}
	void TurnCrank()
	{
		m_state->TurnCrank();
		m_state->Dispense();
	}
	void Refill(const unsigned ballsNum)
	{
		m_state->Refill(ballsNum);
	}
	[[nodiscard]] std::string ToString() const
	{
		return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}
Machine is {}
)",
			m_count, m_count != 1 ? "s" : "", m_state->ToString());
	}

private:
	[[nodiscard]] unsigned GetBallCount() const override
	{
		return m_count;
	}
	void ReleaseBall() override
	{
		if (m_count != 0)
		{
			std::cout << "A gumball comes rolling out the slot..." << std::endl;
			--m_count;
		}
	}
	void SetCoins(unsigned const count) override
	{
		m_coins = count;
	}
	[[nodiscard]] unsigned GetCoinCount() const override
	{
		return m_coins;
	}
	void SetBalls(unsigned const ballsNum) override
	{
		m_count = ballsNum;
	}
	void SetSoldOutState() override
	{
		m_state = &m_soldOutState;
	}
	void SetNoQuarterState() override
	{
		m_state = &m_noQuarterState;
	}
	void SetSoldState() override
	{
		m_state = &m_soldState;
	}
	void SetHasQuarterState() override
	{
		m_state = &m_hasQuarterState;
	}

private:
	unsigned m_count = 0;
	unsigned m_coins = 0;
	SoldState m_soldState;
	SoldOutState m_soldOutState;
	NoQuarterState m_noQuarterState;
	HasQuarterState m_hasQuarterState;
	IState* m_state;
};

} // namespace with_state
