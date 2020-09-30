#!/bin/bash

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    echo "Darwin!"
    brew install cmake || true
    brew upgrade cmake
else


    VERSION=3.13.4

    which cmake
    wget -q https://github.com/Kitware/CMake/releases/download/v${VERSION}/cmake-${VERSION}-Linux-x86_64.tar.gz -O cmake.tar.gz
    tar -xzf cmake.tar.gz

    # Remove the original files and copy the new ones over.
    #sudo rm -rf /usr/local/cmake-3.12.4/*
    sudo cp -r cmake-${VERSION}*/* $(dirname $(dirname $(which cmake)))
    which cmake


fi

    cmake --version
