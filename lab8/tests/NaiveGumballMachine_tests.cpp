#include "../gumballMachine/NaiveGumballMachine.h"
#include "CoutBufferFixture.h"
#include "catch.hpp"

using namespace naive;

SCENARIO_METHOD(CoutBufferFixture, "naive machine with 1 coin")
{
	GIVEN("machine with 3 balls")
	{
		GumballMachine machine(3);

		THEN("It is in no quarter state")
		{
			CHECK(machine.ToString().find("waiting for quarter") != std::string::npos);
		}

		WHEN("insert one quarter")
		{
			machine.InsertQuarter();

			THEN("machine has quarter")
			{
				CHECK(machine.ToString().find("waiting for turn of crank") != std::string::npos);
			}

			WHEN("eject quarter")
			{
				machine.EjectQuarter();

				THEN("machine has no quarter")
				{
					CHECK(machine.ToString().find("waiting for quarter") != std::string::npos);
				}
			}

			WHEN("turn crank")
			{
				machine.TurnCrank();

				THEN("machine release ball")
				{
					CHECK(machine.ToString().find("waiting for quarter") != std::string::npos);
				}
			}
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "naive machine with 2 coins")
{
	GIVEN("machine with 3 balls")
	{
		GumballMachine machine(3);

		WHEN("insert 2 quarters")
		{
			machine.InsertQuarter();
			machine.InsertQuarter();

			THEN("machine has quarter")
			{
				CHECK(machine.ToString().find("waiting for turn of crank") != std::string::npos);
			}

			AND_THEN("can get 2 balls")
			{
				ClearOutput();
				machine.TurnCrank();
				machine.TurnCrank();

				THEN("get 2 balls")
				{
					CHECK(GetOutput() == "You turned...\n"
										 "A gumball comes rolling out the slot...\n"
										 "You turned...\n"
										 "A gumball comes rolling out the slot...\n");
				}

				WHEN("turn of crank again")
				{
					ClearOutput();
					machine.TurnCrank();

					THEN("machine can't give ball")
					{
						CHECK(GetOutput() == "You turned but there's no quarter\n");
					}
				}
			}
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "naive machine with 5 coins")
{
	GIVEN("machine with 3 balls")
	{
		GumballMachine machine(3);

		WHEN("insert 5 quarters")
		{
			machine.InsertQuarter();
			machine.InsertQuarter();
			machine.InsertQuarter();
			machine.InsertQuarter();
			machine.InsertQuarter();

			THEN("all quarters inserted")
			{
				CHECK(GetOutput() == "You inserted a quarter\n"
									 "You inserted a quarter\n"
									 "You inserted a quarter\n"
									 "You inserted a quarter\n"
									 "You inserted a quarter\n");
			}

			AND_THEN("machine is in has quarter state")
			{
				CHECK(machine.ToString().find("waiting for turn of crank") != std::string::npos);
			}

			WHEN("insert one more coin")
			{
				ClearOutput();
				machine.InsertQuarter();

				THEN("machine rejects coin")
				{
					CHECK(GetOutput() == "You can't insert another quarter\n");
					CHECK(machine.ToString().find("waiting for turn of crank") != std::string::npos);
				}
			}

			WHEN("eject coins")
			{
				ClearOutput();
				machine.EjectQuarter();

				THEN("coins ejected")
				{
					CHECK(GetOutput() == "Quarter returned\n");
					CHECK(machine.ToString().find("waiting for quarter") != std::string::npos);
				}

				AND_THEN("can add 5 coins again")
				{
					ClearOutput();
					machine.InsertQuarter();
					machine.InsertQuarter();
					machine.InsertQuarter();
					machine.InsertQuarter();
					machine.InsertQuarter();

					THEN("all quarters inserted")
					{
						CHECK(GetOutput() == "You inserted a quarter\n"
											 "You inserted a quarter\n"
											 "You inserted a quarter\n"
											 "You inserted a quarter\n"
											 "You inserted a quarter\n");
					}

					AND_THEN("machine is in has quarter state")
					{
						CHECK(machine.ToString().find("waiting for turn of crank") != std::string::npos);
					}
				}
			}

			WHEN("turn crank")
			{
				machine.TurnCrank();

				THEN("machine has quarters")
				{
					CHECK(machine.ToString().find("waiting for turn of crank") != std::string::npos);
				}

				WHEN("turn crank again")
				{
					machine.TurnCrank();

					THEN("machine has quarters")
					{
						CHECK(machine.ToString().find("waiting for turn of crank") != std::string::npos);
					}

					WHEN("turn crank again")
					{
						machine.TurnCrank();

						THEN("machine has no more balls")
						{
							CHECK(machine.ToString().find("sold out") != std::string::npos);
						}

						WHEN("eject coins")
						{
							ClearOutput();
							machine.EjectQuarter();

							THEN("coins ejected")
							{
								CHECK(GetOutput() == "Quarter returned\n");

								AND_THEN("can't eject quarter")
								{
									ClearOutput();
									machine.EjectQuarter();
									CHECK(GetOutput() == "You can't eject, you haven't inserted a quarter yet\n");
								}
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "refilling test with naive gumball machine")
{
	GIVEN("an empty gumball machine")
	{
		auto machine = GumballMachine(1);

		WHEN("refill in no quarter state")
		{
			WHEN("refill with 2 balls")
			{
				machine.Refill(2);

				THEN("can buy this balls")
				{
					machine.InsertQuarter();
					machine.InsertQuarter();
					ClearOutput();
					machine.TurnCrank();
					machine.TurnCrank();

					CHECK(GetOutput() == "You turned...\n"
										 "A gumball comes rolling out the slot...\n"
										 "You turned...\n"
										 "A gumball comes rolling out the slot...\n"
										 "Oops, out of gumballs\n");
				}
			}

			WHEN("refill with 0 balls")
			{
				machine.Refill(0);

				THEN("no balls in machine")
				{
					ClearOutput();
					machine.InsertQuarter();

					CHECK(GetOutput() == "You can't insert a quarter, the machine is sold out\n");
				}
			}

		}

		WHEN("refill in has quarter state")
		{
			WHEN("refill with 2 balls")
			{
				machine.InsertQuarter();
				machine.Refill(2);

				THEN("can buy one ball and balls not sold out")
				{
					ClearOutput();
					machine.TurnCrank();

					CHECK(GetOutput() == "You turned...\n"
										 "A gumball comes rolling out the slot...\n");
				}
			}

			WHEN("refill with 0 balls")
			{
				machine.InsertQuarter();
				machine.Refill(0);

				THEN("machine is in sold out state")
				{
					ClearOutput();
					machine.InsertQuarter();

					CHECK(GetOutput() == "You can't insert a quarter, the machine is sold out\n");
				}
			}
		}

		WHEN("refill in sold out state")
		{
			machine.Refill(0);

			WHEN("refill with 2 balls")
			{
				machine.Refill(2);

				THEN("can buy ball")
				{
					machine.InsertQuarter();
					ClearOutput();
					machine.TurnCrank();

					CHECK(GetOutput() == "You turned...\n"
										 "A gumball comes rolling out the slot...\n");
				}
			}

			WHEN("insert quarter and refill")
			{
				machine.Refill(1);
				machine.InsertQuarter();
				machine.Refill(0);
				machine.Refill(2);

				THEN("can buy ball")
				{
					ClearOutput();
					machine.TurnCrank();

					CHECK(GetOutput() == "You turned...\n"
										 "A gumball comes rolling out the slot...\n");
				}
			}
		}
	}
}