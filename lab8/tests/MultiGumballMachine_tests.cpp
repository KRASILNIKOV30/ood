#include "../gumballMachine/GumballMachine.h"
#include "CoutBufferFixture.h"
#include "catch.hpp"

using namespace with_state;

SCENARIO_METHOD(CoutBufferFixture, "multi gumball machine tests")
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

		WHEN("insert 2 quarters")
		{
			machine.InsertQuarter();
			machine.InsertQuarter();

			THEN("machine has quarter")
			{
				CHECK(machine.ToString().find("waiting for turn of crank") != std::string::npos);
			}

			WHEN("can get 2 balls")
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
						CHECK(GetOutput() == "You turned but there's no quarter\n"
											 "You need to pay first\n");
					}
				}
			}
		}

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