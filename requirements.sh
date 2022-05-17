#!/bin/bash

# Variables
LOGGING_REPO_DIR=$PWD
INPUT_ARGS=$@

clone_and_install_fmt() {
    sudo add-apt-repository universe
    sudo apt update
    sudo apt install libfmt-dev
}

install_google_unit_testing_cpp() {
    sudo apt install libgtest-dev
}

clone_and_install_fmt
install_google_unit_testing_cpp
