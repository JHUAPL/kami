[![Build (main)](https://github.com/JHUAPL/kami/actions/workflows/build-main.yml/badge.svg)](https://github.com/JHUAPL/kami/actions/workflows/build-main.yml)
[![Build (develop)](https://github.com/JHUAPL/kami/actions/workflows/build-develop.yml/badge.svg)](https://github.com/JHUAPL/kami/actions/workflows/build-develop.yml)
[![Documentation status](https://readthedocs.org/projects/kami/badge/?version=main)](https://kami.readthedocs.io/en/main/)
[![Release status](https://img.shields.io/github/release/JHUAPL/kami.svg)](https://github.com/JHUAPL/kami/releases)
![License](https://img.shields.io/github/license/JHUAPL/kami)

# Kami is Agent-Based Modeling in Modern C++

## Compiling

```Bash

# Build, test and install the library
git clone https://github.com/k3jph/kami.git
cd kami
conan install -if build .
cmake -B build -DBUILD_SHARED_LIBS:BOOL=FALSE
cmake --build build
cmake --build build --target test
cmake --build build --target install
```

## Conan Package Manager

This library comes with a `conanfile.py` to build it into a Conan package so that
it may be used by external applications/libraries.

### Create Conan Packages

Creating a Conan package is relatively easy. Simple cd into the source directory
and execute the conan create function.

```bash
git clone https://github.com/k3jph/kami.git
cd kami

conan create . kami/develop
```

## Direct Dependencies

* [CLI11](https://github.com/CLIUtils/CLI11)
* [Google Test](https://github.com/google/googletest)
* [neargye-semver](https://github.com/Neargye/semver)
* [spdlog](https://github.com/gabime/spdlog)

CLI11 and spdlog are both used extensively in the examples.
Neither is used directly by the Kami library.

## Contribution guidelines

* Use [GitFlow](http://nvie.com/posts/a-successful-git-branching-model/)
* Use [Google Test](https://github.com/google/googletest)
 
## For more information

* James P. Howard, II <<james.howard@jhu.edu>>
