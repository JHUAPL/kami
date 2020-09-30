#!/bin/bash

set -e
set -x

mkdir -p $HOME/.conan_server
cp .ci-files/conan_server/* $HOME/.conan_server
conan_server &
sleep 3
