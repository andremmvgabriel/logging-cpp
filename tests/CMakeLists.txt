# Utility function
function(add_unit_test test_name)
    add_executable(UUT_${test_name} ${test_name}.cpp)
    target_link_libraries(UUT_${test_name} logging fmt GTest::GTest pthread)
    set_target_properties(
        UUT_${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests
    )
    add_test(UUT_${test_name}_gtest UUT_${test_name} POST_BUILD UUT_${test_name})
    add_custom_command(
        TARGET UUT_${test_name}
        COMMENT "Unit Under Test (UUT): ${test_name}"
        POST_BUILD 
        COMMAND UUT_${test_name}
    )
endfunction()

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

# Tests
add_subdirectory(formatters)