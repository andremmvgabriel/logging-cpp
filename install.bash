#!/bin/bash

# Variables
CURRENT_DIR=$PWD

# Making sure the project is built...

# Checks if the build directory already exists
if [ ! -d "$CURRENT_DIR/build" ]; then
    sudo mkdir "build"
fi

# Goes into build directory
cd build

# Builds the project
sudo cmake ..
sudo make

# Goes back on the directories tree
cd ..

# Checks if the library file already exists in the user local lib folder
if [ -f "/usr/local/lib/liblogging.a" ]; then
    #if [[ $* == *-y* ]]; then
    #    echo "What does this do ehre?"
    #fi
    echo "> Logging library already detected in the libraries folder."
else
    echo "> Logging library was not detected in the libraries folder... Installing..."

    sudo cp "$CURRENT_DIR/lib/liblogging.a" "/usr/local/lib/liblogging.a"

    echo "> Logging library successfully installed."
fi

# Checks if the header file already exists in the user local include folder
if [ -f "/usr/local/include/logging.hpp" ]; then
    #if [[ $* == *-y* ]]; then
    #    echo "What does this do ehre?"
    #fi
    echo "> Logging library header file already detected in the user local include folder."
else
    echo "> Logging library header file was not detected in the user local include folder... Adding it..."

    sudo cp "$CURRENT_DIR/include/logging.hpp" "/usr/local/include/logging.hpp"

    echo "> Logging library header file successfully added."
fi