#include "GumballMachine.h"
#include "../../lab5_cmake/menu/Menu.h"

using namespace with_state;

int main()
{
	GumballMachine gm(3);
	Menu menu(std::cin, std::cout, {
		{
			"InsertQuarter",
			"insert quarter in gumball machine",
			[&] (auto& _) {
				gm.InsertQuarter();
			}
		},
		{
			"EjectQuarter",
			"eject quarter from gumball machine",
			[&] (auto& _) {
				gm.EjectQuarter();
			}
		},
		{
			"TurnCrank",
			"turn crank to buy gumball",
			[&] (auto& _) {
				gm.TurnCrank();
			}
		},
		{
			"Refill",
			"Refill <ballsNum>; refill machine",
			[&] (auto& input) {
				size_t ballsNum;
				input >> ballsNum;
				gm.Refill(ballsNum);
			}
		},
		{
			"ToString",
			"output machines state",
			[&] (auto& _) {
				std::cout << gm.ToString();
			}
		},
	});
	menu.AddItem("exit", "exit program", [&] (auto& _) { menu.Exit(); });
	menu.AddItem("help", "output instructions", [&] (auto& _) { menu.ShowInstructions(); });

	menu.Run();

	return EXIT_SUCCESS;
}