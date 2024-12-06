add_executable(tiles_tests
        tiles/Image.cpp
        tiles/Image.h
        tiles/Geom.h
        tiles/Drawer.cpp
        tiles/Drawer.h
        tiles/Cow.h
        tiles/Tile.h
        tests/Tile_tests.cpp
        tests/Image_tests.cpp
)

add_executable(tiles
        tiles/main.cpp
        tiles/Image.cpp
        tiles/Image.h
        tiles/Geom.h
        tiles/Drawer.cpp
        tiles/Drawer.h
        tiles/Cow.h
        tiles/Tile.h
)

target_link_libraries(tiles_tests PUBLIC catch2)
add_test(tiles_tests COMMAND tiles_tests)