cmake_minimum_required(VERSION 3.10)

# Set the project name (and version?)
project(Logging_Examples)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)

add_executable( Main
    main.cpp
)
target_link_libraries ( Main
    logging
    -lboost_filesystem
)