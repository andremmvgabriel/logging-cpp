#!/bin/bash

# Variables
LOGGING_REPO_DIR=$PWD
INPUT_ARGS=$@

clone_and_install_fmt() {
    sudo add-apt-repository universe
    sudo apt update
    sudo apt install libfmt-dev
}

clone_and_install_fmt
