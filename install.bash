#!/bin/bash

# Variables
CURRENT_DIR=$PWD
FORCE_INSTALL="F"

# Checks for force install flag
while test $# -gt 0; do
    case "$1" in
        -f )
            FORCE_INSTALL="T"
            shift
        ;;
        -force )
            FORCE_INSTALL="T"
            shift
        ;;
        -update )
            FORCE_INSTALL="T"
            shift
        ;;
    esac
done

# Creates a build folder
cmake -E make_directory build

# Goes into build directory
cd build

# Builds the project
cmake ..
cmake --build .

# Goes back on the directories tree
cd ..

# Checks if the library file already exists in the user local lib folder
if [ -f "/usr/local/lib/liblogging.a" ]; then
    if [ $FORCE_INSTALL == "T" ]; then
        echo "> Updating Logging library lib file..."

        sudo rm "/usr/local/lib/liblogging.a"

        sudo cp "$CURRENT_DIR/lib/liblogging.a" "/usr/local/lib/liblogging.a"

        echo "> Logging library lib file updated."
    else 
        echo "> Logging library already detected in the libraries folder."
    fi
else
    echo "> Logging library was not detected in the libraries folder... Installing..."

    sudo cp "$CURRENT_DIR/lib/liblogging.a" "/usr/local/lib/liblogging.a"

    echo "> Logging library successfully installed."
fi

# Checks if the header file already exists in the user local include folder
if [ -f "/usr/local/include/logging.hpp" ]; then
    if [ $FORCE_INSTALL == "T" ]; then
        echo "> Updating Logging library header file..."

        sudo rm "/usr/local/include/logging.hpp"

        sudo cp "$CURRENT_DIR/include/logging.hpp" "/usr/local/include/logging.hpp"

        echo "> Logging library header file updated."
    else
        echo "> Logging library header file already detected in the user local include folder."
    fi
else
    echo "> Logging library header file was not detected in the user local include folder... Adding it..."

    sudo cp "$CURRENT_DIR/include/logging.hpp" "/usr/local/include/logging.hpp"

    echo "> Logging library header file successfully added."
fi
