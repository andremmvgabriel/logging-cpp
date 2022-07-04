# Utility function
function(add_example example_name)
    add_executable(${example_name} ${example_name}.cpp)
    target_link_libraries(${example_name} logging)# fmt pthread)
    set_target_properties(
        ${example_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples
        EXCLUDE_FROM_ALL 1
    )
endfunction()

# Examples
add_example( simple_logging )
list ( APPEND examples_bins simple_logging )

# Creates a target flag for the example executables
add_custom_target (
    examples ${examples_bins} # Target name + Executables
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/logs # Creates the logs directory if the target is specified on build
)
