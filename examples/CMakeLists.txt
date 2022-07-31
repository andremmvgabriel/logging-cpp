# Utility function
function(add_example example_name)
    add_executable(${example_name}.example ${example_name}.cpp)
    target_link_libraries(${example_name}.example logging fmt pthread)
    set_target_properties(
        ${example_name}.example
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        EXCLUDE_FROM_ALL 1
    )
    set( examples_suit ${examples_suit} ${example_name}.example PARENT_SCOPE )
endfunction(add_example)

# Examples
add_example( simple_logging )
add_example( logger_handler )
add_example( chained_logging )
add_example( logging_with_formatters )
add_example( logging_with_handlers )

# Creates a target flag for the example executables
add_custom_target ( examples
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/logs
)
message( STATUS ${examples_suit} )
add_dependencies ( examples ${examples_suit} )
