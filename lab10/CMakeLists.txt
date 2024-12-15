set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

qt_add_executable(shapes
        src/main.cpp
        src/ui_shapes.h
        src/Frame.h
        src/model/Shape.h
        src/model/Triangle.h
        src/model/Rectangle.h
        src/model/Ellipse.h
)

add_executable(shapes_tests
        src/Frame.h
        src/model/Shape.h
        src/model/Triangle.h
        src/model/Rectangle.h
        src/model/Ellipse.h
        src/tests/Shapes_tests.cpp
)

target_link_libraries(shapes PRIVATE Qt6::Widgets)

target_link_libraries(shapes_tests PUBLIC catch2)
add_test(shapes_tests COMMAND shapes_tests)