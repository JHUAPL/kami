# Installation

## Requirements

The core of Kami, `libkami` has no requirements beyond a modern C++ compiler.  However, both the examples provided and 
the 

## Compiling

To compile and test locally in kami/build:

    git clone https://github.com/k3jph/kami.git
    cd kami
    conan install -if build .
    cmake -B build -DBUILD_SHARED_LIBS:BOOL=FALSE
    cmake --build build
    cmake --build build --target test

## Conan Installation (Local)

To install via [Conan](https://conan.io/):

    conan create . kami/develop

