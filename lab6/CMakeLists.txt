add_executable(object-adapter
        lib/GraphicsLib.h
        lib/ShapeDrawingLib.h
        lib/ModernGraphicsLib.h
        main.cpp
        ModernGraphicsRendererObjectAdapter.h
)

add_executable(class-adapter
        lib/GraphicsLib.h
        lib/ShapeDrawingLib.h
        lib/ModernGraphicsLib.h
        main.cpp
        ModernGraphicsRendererClassAdapter.h
)

add_executable(Adapter_tests
        tests/Adapter_tests.cpp
        lib/GraphicsLib.h
        lib/ShapeDrawingLib.h
        lib/ModernGraphicsLib.h
)

target_link_libraries(Adapter_tests PUBLIC catch2)
add_test(NAME Adapter_tests COMMAND Adapter_tests)

