add_executable(HtmlEditor_tests
        tests/menu_tests.cpp
        sources/Menu.cpp
        headers/Menu.h
)

target_link_libraries(HtmlEditor_tests PUBLIC catch2)
add_test(NAME HtmlEditor_tests COMMAND HtmlEditor_tests)

