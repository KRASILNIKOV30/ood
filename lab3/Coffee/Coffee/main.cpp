#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;


/*
Функциональный объект, создающий лимонную добавку
*/
struct MakeLemon
{
	MakeLemon(unsigned quantity)
		:m_quantity(quantity)
	{}

	auto operator()(IBeveragePtr&& beverage)const
	{
		return make_unique<CLemon>(move(beverage), m_quantity);
	}
private:
	unsigned m_quantity;
};

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<IBeveragePtr(IBeveragePtr&&)> MakeCinnamon()
{
	return [](IBeveragePtr&& b) {
		return make_unique<CCinnamon>(move(b));
	};
}

/*
Возвращает функцию, декорирующую напиток определенной добавкой

Параметры шаблона:
	Condiment - класс добавки, конструктор которого в качестве первого аргумента
				принимает IBeveragePtr&& оборачиваемого напитка
	Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
	// Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
	// Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
	// конструктору декоратора через make_unique
	return [=](auto&& b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator << (Component&& component, const Decorator& decorate)
{
	return decorate(forward<Component>(component));
}

void DialogWithUser()
{
	cout << "Type 1 for coffee, 2 for tea or 3 for milkshake\n";
	int beverageChoice;
	cin >> beverageChoice;

	unique_ptr<IBeverage> beverage;

	if (beverageChoice == 1)
	{
		beverage = make_unique<CCoffee>();

		int coffeeChoice;
		cout << "1 - Cappuccino, 2 - Latte" << endl;
		cin >> coffeeChoice;

		if (coffeeChoice == 1)
		{
			beverage = make_unique<CCappuccino>();
		}
		else if (coffeeChoice == 2)
		{
			beverage = make_unique<CLatte>();
		}
		else
		{
			return;
		}
		
		int portionChoice;
		cout << "1 - Standard, 2 - Double" << endl;
		cin >> portionChoice;

		if (portionChoice == 2)
		{
				beverage = move(beverage) << MakeCondiment<CDouble>();
		}
	}
	else if (beverageChoice == 2)
	{
		int teaChoice;
		cout << "1 - Mi Lan Xiang, 2 - Da Hong Pao, 3 - Tie Guan Yin, 4 - Feng Huang Dan Cong" << endl;
		cin >> teaChoice;
		if (teaChoice == 1)
		{
			beverage = make_unique<CTea>(TeaSort::MiLanXiang);
		}
		else if (teaChoice == 2)
		{
			beverage = make_unique<CTea>(TeaSort::DaHongPao);
		}
		else if (teaChoice == 3)
		{
			beverage = make_unique<CTea>(TeaSort::TieGuanYin);
		}
		else if (teaChoice == 4)
		{
			beverage = make_unique<CTea>(TeaSort::FengHuangDanCong);
		}
		else
		{
			return;
		}
		
	}
	else if (beverageChoice == 3)
	{
		int sizeChoice;
		cout << "1 - Small, 2 - Standard, 3 - Big" << endl;
		cin >> sizeChoice;

		if (sizeChoice == 1)
		{
			beverage = make_unique<CMilkshake>(PortionSize::Small);
		}
		else if (sizeChoice == 2)
		{
			beverage = make_unique<CMilkshake>(PortionSize::Standard);
		}
		else if (sizeChoice == 3)
		{
			beverage = make_unique<CMilkshake>(PortionSize::Big);
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}

	int condimentChoice;
	for (;;)
	{
		cout << "1 - Lemon, 2 - Cinnamon, 3 - Cream, 4 - Chocolate, 0 - Checkout" << endl;
		cin >> condimentChoice;

		if (condimentChoice == 1)
		{
			beverage = move(beverage) << MakeCondiment<CLemon>(1);
		}
		else if (condimentChoice == 2)
		{
			beverage = move(beverage) << MakeCondiment<CCinnamon>();
		}
		else if (condimentChoice == 3)
		{
			beverage = move(beverage) << MakeCondiment<CCream>();
		}
		else if (condimentChoice == 4)
		{
			int chocolateQuantity;
			cout << "Enter quantity of chocolate" << endl;
			cin >> chocolateQuantity;
			if (chocolateQuantity > 5)
			{
				cout << "Too many chocolate, max: 5" << endl;
			}
			else
			{
				beverage = move(beverage) << MakeCondiment<CChocolate>(chocolateQuantity);
			}
		}
		else if (condimentChoice == 0)
		{
			break;
		}
		else
		{
			return;
		}
	}

	cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
}


int main()
{
	DialogWithUser();
}
