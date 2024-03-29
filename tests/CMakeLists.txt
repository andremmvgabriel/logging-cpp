# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

# Utility function
function(add_unit_test test_name)
    add_executable(UUT_${test_name} ${test_name}.cpp)
    target_link_libraries(UUT_${test_name} logging fmt GTest::GTest pthread)
    set_target_properties(
        UUT_${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests
        EXCLUDE_FROM_ALL 1
    )
    add_test(UUT_${test_name}_gtest UUT_${test_name} POST_BUILD UUT_${test_name})
    add_custom_command(
        TARGET UUT_${test_name}
        COMMENT "Unit Under Test (UUT): ${test_name}"
        POST_BUILD 
        COMMAND UUT_${test_name}
    )
    set( tests_suit ${tests_suit} UUT_${test_name} PARENT_SCOPE )
endfunction(add_unit_test)

# Tests
add_subdirectory(core)
add_subdirectory(formatters)
add_subdirectory(handlers)

add_custom_target ( tests )
add_dependencies ( tests ${tests_suit} )
