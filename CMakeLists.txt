cmake_minimum_required(VERSION 3.10)

# Set the project name (and version?)
project(Logging)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Changes the binary, static lib, and libraries default paths of the CMake build, respectively
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)

INCLUDE_DIRECTORIES ( include )

set( src_logging_lib
    src/gabe/logging/logging.cpp

    src/gabe/logging/Manager.cpp
    src/gabe/logging/LoggerHandler.cpp

    src/gabe/logging/core/Logger.cpp
    src/gabe/logging/core/Sink.cpp

    src/gabe/logging/handlers/Handler.cpp
    src/gabe/logging/handlers/TimeRotatingFileHandler.cpp

    src/gabe/logging/formatters/Formatter.cpp
    src/gabe/logging/formatters/Calendar.cpp
    src/gabe/logging/formatters/Time.cpp
)
add_library( logging STATIC ${src_logging_lib} )

add_executable(Main main.cpp)
target_link_libraries(Main logging fmt)

add_executable(NewAPI new_api_main.cpp)
target_link_libraries(NewAPI logging fmt)
