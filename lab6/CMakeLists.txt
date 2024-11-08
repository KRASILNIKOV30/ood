add_executable(Adapter
)

add_executable(Adapter_tests

)

target_link_libraries(Adapter_tests PUBLIC catch2)
add_test(NAME Adapter_tests COMMAND Adapter_tests)

