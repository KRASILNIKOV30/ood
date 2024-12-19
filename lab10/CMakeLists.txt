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
        src/model/IShape.h
        src/model/IShapes.h
        src/model/Shapes.h
        src/model/Shapes.cpp
        src/repository/Repository.h
        src/signals/SignallingValue.h
        src/appModel/IShapeAppModel.h
        src/appModel/ShapeAppModel.h
        src/appModel/IShapesAppModel.h
)

add_executable(shapes_tests
        src/Frame.h
        src/model/Shape.h
        src/model/Triangle.h
        src/model/Rectangle.h
        src/model/Ellipse.h
        src/tests/Shape_tests.cpp
        src/model/IShape.h
        src/model/Shapes.h
        src/model/Shapes.cpp
        src/tests/Shapes_tests.cpp
        src/repository/Repository.h
        src/signals/SignallingValue.h
        src/tests/Repository_tests.cpp
        src/appModel/IShapeAppModel.h
        src/appModel/ShapeAppModel.h
        src/tests/ShapeAppModel_tests.cpp
        src/appModel/IShapesAppModel.h
)

include(FetchContent)

FetchContent_Declare(GSL
        GIT_REPOSITORY "https://github.com/microsoft/GSL"
        GIT_TAG "v4.1.0"
        GIT_SHALLOW ON
)

FetchContent_MakeAvailable(GSL)

target_link_libraries(shapes PRIVATE Microsoft.GSL::GSL)
target_link_libraries(shapes_tests PRIVATE Microsoft.GSL::GSL)

target_link_libraries(shapes PRIVATE Qt6::Widgets)
target_link_libraries(shapes_tests PUBLIC catch2)

add_test(shapes_tests COMMAND shapes_tests)