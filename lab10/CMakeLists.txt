set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(shapes
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
        src/appModel/ShapesAppModel.cpp
        src/appModel/ShapesAppModel.h
        src/history/AbstractUndoableEdit.cpp
        src/history/AbstractUndoableEdit.h
        src/history/CompoundEdit.cpp
        src/history/CompoundEdit.h
        src/history/IUndoableEdit.h
        src/history/IUndoableEdit_fwd.h
        src/history/UndoManager.cpp
        src/history/UndoManager.h
        src/model/ShapeFactory.h
        src/history/edit/AddShapeEdit.h
        src/history/edit/RemoveShapeEdit.h
        src/viewModel/IShapeViewModel.h
        src/viewModel/ShapeViewModel.h
        src/viewModel/IShapesViewModel.h
        src/viewModel/ShapesViewModel.h
        src/viewModel/ShapesViewModel.cpp
        src/view/IShapeView.h
        src/view/ShapeView.h
        src/view/shapes/RectangleView.h
        src/view/ShapeViewFactory.h
        src/view/canvas/ICanvas.h
        src/view/canvas/Canvas.cpp
        src/view/canvas/Canvas.h
        src/view/selection/ISelection.h
        src/view/selection/Selection.cpp
        src/view/selection/Selection.h
        src/view/shapes/TriangleView.h
        src/view/shapes/EllipseView.h
        src/EditSink.h
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
        src/appModel/ShapesAppModel.cpp
        src/appModel/ShapesAppModel.h
        src/history/AbstractUndoableEdit.cpp
        src/history/AbstractUndoableEdit.h
        src/history/CompoundEdit.cpp
        src/history/CompoundEdit.h
        src/history/IUndoableEdit.h
        src/history/IUndoableEdit_fwd.h
        src/history/UndoManager.cpp
        src/history/UndoManager.h
        src/tests/ShapesAppModel_tests.cpp
        src/model/ShapeFactory.h
        src/history/edit/AddShapeEdit.h
        src/tests/UndoManager_tests.cpp
        src/history/edit/RemoveShapeEdit.h
        src/viewModel/IShapeViewModel.h
        src/viewModel/IShapesViewModel.h
        src/viewModel/ShapesViewModel.h
        src/viewModel/ShapesViewModel.cpp
        src/view/IShapeView.h
        src/EditSink.h
)

include(FetchContent)

FetchContent_Declare(GSL
        GIT_REPOSITORY "https://github.com/microsoft/GSL"
        GIT_TAG "v4.1.0"
        GIT_SHALLOW ON
)

find_package(wxWidgets REQUIRED COMPONENTS core base)
if (wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif ()

FetchContent_MakeAvailable(GSL)

target_link_libraries(shapes PRIVATE Microsoft.GSL::GSL)
target_link_libraries(shapes_tests PRIVATE Microsoft.GSL::GSL)

target_link_libraries(shapes PRIVATE ${wxWidgets_LIBRARIES})
target_link_libraries(shapes_tests PUBLIC catch2)

add_test(shapes_tests COMMAND shapes_tests)