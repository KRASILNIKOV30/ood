#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../headers/Menu.h"

SCENARIO("some scenario")
{
    GIVEN("Menu")
    {
        THEN("test")
        {
            Menu menu;
            CHECK(menu.Test() == 25);
        }
    }
}
