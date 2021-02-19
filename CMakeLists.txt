cmake_minimum_required(VERSION 3.10)

# Set the project name (and version?)
project(Logger)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED)

################
#   Packages   #
################

add_executable( Main
    main.cpp
    TextUtils.cpp
    Logger.cpp
)
target_link_libraries( Main
    -lboost_filesystem
    -lboost_system
)