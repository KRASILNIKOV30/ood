set(CMAKE_CXX_STANDARD 20)

add_executable(gumball-machine-tests
        gumballMachine/GumballMachine.h
        tests/GumballMachine_tests.cpp
        tests/MultiGumballMachine_tests.cpp
        gumballMachine/NaiveGumballMachine.h
        tests/NaiveGumballMachine_tests.cpp
)

add_executable(gumball-machine
        gumballMachine/GumballMachine.h
        gumballMachine/NaiveGumballMachine.h
        gumballMachine/Menu.h
        gumballMachine/main.cpp
)

set_target_properties(gumball-machine-tests PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(gumball-machine PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(gumball-machine-tests PUBLIC catch2)
target_link_libraries(gumball-machine-tests PUBLIC coutBuffer)
add_test(NAME gumball-machine-tests COMMAND gumball-machine-tests)