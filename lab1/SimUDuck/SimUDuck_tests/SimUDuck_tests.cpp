﻿#include "../../../external/catch2/catch.hpp"
#include <sstream>
#include <iostream>
#include "../SimUDuck/lib/Duck/DecoyDuck.h"
#include "../SimUDuck/lib/Duck/MallardDuck.h"
#include "../SimUDuck/lib/Duck/ModelDuck.h"
#include "../SimUDuck/lib/Duck/RedheadDuck.h"
#include "../SimUDuck/lib/Duck/RubberDuck.h"
#include "../SimUDuck/lib/DuckFunctions.h"

struct CoutBufferFixture
{
	std::stringstream buffer;
	std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

	std::string Get()
	{
		return buffer.str();
	}

	std::string Clear()
	{
		buffer.str(std::string());
	}
};

SCENARIO_METHOD(CoutBufferFixture, "Play with mallard duck")
{
	WHEN("Create and play with mallard duck")
	{
		MallardDuck mallardDuck;
		PlayWithDuck(mallardDuck);

		THEN("Mallard duck can quack, flying with wings and dancing")
		{
			CHECK(buffer.str() == "I'm mallard duck\nQuack Quack!!!\n1: I'm flying with wings!!\nI'm dancing a waltz\n\n");
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Play with redhead duck")
{
	WHEN("Create and play with redhead duck")
	{
		RedheadDuck redheadDuck;
		PlayWithDuck(redheadDuck);

		THEN("Redhead duck can quack, flying with wings and dancing")
		{
			CHECK(buffer.str() == "I'm redhead duck\nQuack Quack!!!\n1: I'm flying with wings!!\nI'm dancing a minuet\n\n");
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Play with rubber duck")
{
	WHEN("Create and play with rubber duck")
	{
		RubberDuck rubberDuck;
		PlayWithDuck(rubberDuck);

		THEN("Rubber duck can squeek")
		{
			CHECK(buffer.str() == "I'm rubber duck\nSqueek!!!\n\n");
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Play with decoy duck")
{
	WHEN("Create and play with decoy duck")
	{
		DecoyDuck decoyDuck;
		PlayWithDuck(decoyDuck);

		THEN("Decoy duck can't do anything")
		{
			CHECK(buffer.str() == "I'm decoy duck\n\n");
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Play with model duck")
{
	WHEN("Create and play with model duck")
	{
		ModelDuck modelDuck;
		PlayWithDuck(modelDuck);

		THEN("Model duck can quack")
		{
			CHECK(buffer.str() == "I'm model duck\nQuack Quack!!!\n\n");
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Change duck flying")
{
	WHEN("Create model duck and change duck flying")
	{
		ModelDuck modelDuck;
		modelDuck.SetFlyBehavior(std::make_unique<FlyWithWings>());
		PlayWithDuck(modelDuck);

		THEN("Model duck can quack and flying with wings")
		{
			CHECK(buffer.str() == "I'm model duck\nQuack Quack!!!\n1: I'm flying with wings!!\n\n");
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Mallard duck fly many times")
{
	WHEN("Play with mallard duck for the first time")
	{
		MallardDuck mallardDuck;
		PlayWithDuck(mallardDuck);

		THEN("Mallard duck fly for the first time")
		{
			CHECK(buffer.str() == "I'm mallard duck\nQuack Quack!!!\n1: I'm flying with wings!!\nI'm dancing a waltz\n\n");
		}

		AND_WHEN("Play with mallard duck for the second time")
		{
			buffer.str(std::string());
			PlayWithDuck(mallardDuck);

			THEN("Mallard duck fly for the second time")
			{
				CHECK(buffer.str() == "I'm mallard duck\nQuack Quack!!!\n2: I'm flying with wings!!\nI'm dancing a waltz\n\n");
			}
		}
	}
}

