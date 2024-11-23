set(CMAKE_CXX_STANDARD 20)

add_executable(gumball-machine
        gumballMachine/GumballMachine.h
        tests/GumballMachine_tests.cpp
)

set_target_properties(gumball-machine PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(gumball-machine PUBLIC catch2)
target_link_libraries(gumball-machine PUBLIC coutBuffer)
add_test(NAME gumball-machine COMMAND gumball-machine)