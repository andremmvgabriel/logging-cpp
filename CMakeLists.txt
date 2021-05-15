cmake_minimum_required(VERSION 3.10)

# Set the project name (and version?)
project(Logger)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Finds BOOST package
find_package(Boost REQUIRED)

# Changes the binary, static lib, and libraries default paths of the CMake build, respectively
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)

INCLUDE_DIRECTORIES ( include )

add_library( Logger STATIC Logger.cpp )
target_link_libraries( Logger
    -lboost_filesystem
    -lboost_system
)

add_executable( Main
    main.cpp
)
target_link_libraries( Main    
    Logger
)
