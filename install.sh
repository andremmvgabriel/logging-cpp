#!/bin/bash

# Variables
LOGGING_REPO_DIR=$PWD

# Flags
UPDATE="False"

# Checks for force install flag
while test $# -gt 0; do
    case "$1" in
        -u )
            UPDATE="True"
            shift
        ;;
        -update )
            UPDATE="True"
            shift
        ;;
    esac
done

build_and_install () {
    # Creates a build folder
    mkdir -p build

    # Goes into build directory
    cd build

    # Builds the project
    cmake ..
    cmake --build .

    sudo cp "$LOGGING_REPO_DIR/lib/liblogging.a" "/usr/local/lib/liblogging.a"
    sudo cp "$LOGGING_REPO_DIR/include/logging.hpp" "/usr/local/include/logging.hpp"
}

# Checks if the library and header files exist in the user local folders
if [ -f "/usr/local/lib/liblogging.a" ] && [ -f "/usr/local/include/logging.hpp" ]; then
    if [ $UPDATE == "True" ]; then
        echo "> Updating Logging library files..."
        build_and_install
        echo "    Logging library files updated."
    else 
        echo "> Logging library detected in the libraries folder. Skipping installation..."
    fi
else
    echo "> Logging library was not detected in the libraries folder. Installing..."
    build_and_install
    echo "    Logging library successfully installed."
fi
