# Installation

## Requirements

The core of Kami, `libkami`, has no requirements beyond a modern C++ compiler and `neargye-semver/0.3.0`. However, both the examples provided and
the unit tests provided rely on three additional C++ packages.  The full list is:

* cli11/1.9.1
* gtest/cci.20210126
* neargye-semver/0.3.0"
* spdlog/1.8.5
* fmt/7.1.3

[`Google Test`](https://github.com/google/googletest) provides a
unit testing framework.  [`CLI11`](https://cliutils.github.io/CLI11/)
provides a command line interface for each of the utilities that
makeup the examples.  [`spdlog`](https://github.com/gabime/spdlog)
provides a uniform output interface. Coupled with a command line
option to set the output level, `spdlog` allows the unit tests and
example programs to provide variable output levels depending on the
users needs. Finally, [`fmt`](https://fmt.dev/) is required by
`spdlog` for simple and easy string formatting.

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

