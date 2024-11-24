#define CATCH_CONFIG_MAIN
#include "../gumballMachine/GumballMachine.h"
#include "CoutBufferFixture.h"
#include "catch.hpp"

using namespace with_state;

class MockGumballMachine final : public IGumballMachine
{
public:
	MockGumballMachine(unsigned const ballCount)
		: m_ballCount(ballCount)
	{
	}
	void ReleaseBall() override {};
	[[nodiscard]] unsigned GetBallCount() const override { return m_ballCount; }
	void SetSoldOutState() override {}
	void SetNoQuarterState() override {}
	void SetSoldState() override {}
	void SetHasQuarterState() override {}
	void SetCoins(unsigned count) override {}
	[[nodiscard]] unsigned GetCoinCount() const override { return 0; }

private:
	unsigned m_ballCount;
};

SCENARIO_METHOD(CoutBufferFixture, "GumballMachine behavior in different states")
{
	GIVEN("A gumball machine with 2 ball")
	{
		GumballMachine machine(2);

		WHEN("The machine is in no quarter state")
		{
			THEN("The machine should be waiting for a quarter")
			{
				REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
			}

			WHEN("A quarter is inserted")
			{
				machine.InsertQuarter();

				THEN("The machine should be in has quarter state")
				{
					REQUIRE(machine.ToString().find("waiting for turn of crank") != std::string::npos);
				}

				WHEN("eject quarter")
				{
					machine.EjectQuarter();

					THEN("The machine should be in has quarter state")
					{
						REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
					}
				}
			}
		}

		GIVEN("The machine has a quarter")
		{
			machine.InsertQuarter();

			WHEN("The crank is turned")
			{
				machine.TurnCrank();

				THEN("The machine should dispense a gumball")
				{
					REQUIRE(machine.ToString().find("waiting for quarter") != std::string::npos);
				}

				AND_WHEN("The machine has one more ball")
				{
					machine.InsertQuarter();
					machine.TurnCrank();

					THEN("The machine is in sold out state")
					{
						REQUIRE(machine.ToString().find("sold out") != std::string::npos);
					}
				}
			}
		}

		GIVEN("The machine is sold out")
		{
			GumballMachine emptyMachine(0);
			emptyMachine.InsertQuarter();

			WHEN("The quarter is inserted")
			{
				THEN("The machine should indicate that it is sold out")
				{
					REQUIRE(emptyMachine.ToString().find("sold out") != std::string::npos);
				}
			}
		}

		GIVEN("The machine is in sold out state")
		{
			GumballMachine emptyMachine(0);

			WHEN("The user inserts a quarter")
			{
				emptyMachine.InsertQuarter();

				THEN("The machine should reject the quarter")
				{
					REQUIRE(GetOutput() == "You can't insert a quarter, the machine is sold out\n");
				}
			}
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Testing the behavior of each state of the GumballMachine", "[gumball-machine]")
{

	GIVEN("A gumball machine with 1 ball")
	{
		MockGumballMachine machine(1);

		WHEN("The machine is in NoQuarterState")
		{
			NoQuarterState noQuarterState(machine);

			THEN("The state should correctly handle InsertQuarter()")
			{
				noQuarterState.InsertQuarter();
				REQUIRE(GetOutput() == "You inserted a quarter\n");
				ClearOutput();
			}

			THEN("The state should correctly handle TurnCrank()")
			{
				noQuarterState.TurnCrank();
				REQUIRE(GetOutput() == "You turned but there's no quarter\n");
				ClearOutput();
			}

			THEN("The state should correctly handle EjectQuarter()")
			{
				noQuarterState.EjectQuarter();
				REQUIRE(GetOutput() == "You haven't inserted a quarter\n");
				ClearOutput();
			}

			THEN("The state should correctly handle Dispense()")
			{
				noQuarterState.Dispense();
				REQUIRE(GetOutput() == "You need to pay first\n");
				ClearOutput();
			}
		}

		GIVEN("The machine is in HasQuarterState")
		{
			HasQuarterState hasQuarterState(machine);

			WHEN("The crank is turned")
			{
				THEN("The machine should transition to SoldState")
				{
					hasQuarterState.TurnCrank();
					REQUIRE(GetOutput() == "You turned...\n");
					ClearOutput();
				}
			}

			WHEN("The quarter is ejected")
			{
				THEN("The state should transition to NoQuarterState")
				{
					hasQuarterState.EjectQuarter();
					REQUIRE(GetOutput() == "Quarter returned\n");
					ClearOutput();
				}
			}

			THEN("The state should correctly handle Dispense()")
			{
				hasQuarterState.Dispense();
				REQUIRE(GetOutput() == "No gumball dispensed\n");
				ClearOutput();
			}
		}

		GIVEN("The machine is in SoldState")
		{
			SoldState soldState(machine);

			THEN("The state should correctly handle InsertQuarter()")
			{
				soldState.InsertQuarter();
				REQUIRE(GetOutput() == "Please wait, we're already giving you a gumball\n");
				ClearOutput();
			}

			THEN("The state should correctly handle EjectQuarter()")
			{
				soldState.EjectQuarter();
				REQUIRE(GetOutput() == "Sorry you already turned the crank\n");
				ClearOutput();
			}

			THEN("The state should correctly handle TurnCrank()")
			{
				soldState.TurnCrank();
				REQUIRE(GetOutput() == "Turning twice doesn't get you another gumball\n");
				ClearOutput();
			}

			THEN("The state should correctly handle Dispense()")
			{
				soldState.Dispense();
				REQUIRE(GetOutput().empty());
			}

			WHEN("state with empty machine")
			{
				MockGumballMachine emptyMachine(0);
				SoldState soldStateEmpty(emptyMachine);
				soldStateEmpty.Dispense();

				THEN("Can not get gumballs")
				{
					REQUIRE(GetOutput() == "Oops, out of gumballs\n");
				}
			}
		}

		GIVEN("The machine is in SoldOutState")
		{
			SoldOutState soldOutState(machine);

			THEN("The state should correctly handle InsertQuarter()")
			{
				soldOutState.InsertQuarter();
				REQUIRE(GetOutput() == "You can't insert a quarter, the machine is sold out\n");
				ClearOutput();
			}

			THEN("The state should correctly handle EjectQuarter()")
			{
				soldOutState.EjectQuarter();
				REQUIRE(GetOutput() == "You can't eject, you haven't inserted a quarter yet\n");
				ClearOutput();
			}

			THEN("The state should correctly handle TurnCrank()")
			{
				soldOutState.TurnCrank();
				REQUIRE(GetOutput() == "You turned but there's no gumballs\n");
				ClearOutput();
			}

			THEN("The state should correctly handle Dispense()")
			{
				soldOutState.Dispense();
				REQUIRE(GetOutput() == "No gumball dispensed\n");
				ClearOutput();
			}
		}
	}
}
