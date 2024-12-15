set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

qt_add_executable(shapes
        src/main.cpp
        src/ui_shapes.h
)

target_link_libraries(shapes PRIVATE Qt6::Widgets)