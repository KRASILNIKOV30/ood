#include "catch.hpp"
#include "../headers/Menu.h"

SCENARIO("some scenario2")
{
    GIVEN("Menu2")
    {
        THEN("test2")
        {
            Menu menu;
            CHECK(menu.Test() == 25);
        }
    }
}
