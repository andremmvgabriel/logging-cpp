cmake_minimum_required(VERSION 3.10)

# Set the project name (and version?)
project(Logging_Examples)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)

add_executable( Main2
    main2.cpp
)
target_link_libraries ( Main2
    -llogging
)