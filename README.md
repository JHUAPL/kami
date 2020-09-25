# C++ Library Template

# Features

* Multimodule library: Three libraries wrapped in a single namespace: `foo::bar`, `foo::cat` and `foo::dog`
* Auto-generated EXPORT headers for Windows DLLs
* Auto-generated CMake config files for installation
* Unit tests
* Conan Package Manager Integration
* Gitlab-CI integration
  * Builds the library with gcc/clang verions
  * Tests that the find_package() method works
  * Builds the Conan Package
  * Tests the cmake, cmake_paths, and cmake_find_package generators work
* **[to do]** CPack generation.

# Compiling

```Bash

# Build, test and install the library
git clone https://github.com/k3jph/kami.git
cd kami
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/tmp/kami -DBUILD_SHARED_LIBS:BOOL=TRUE
cmake --build .
ctest -C Debug
cmake --build . --target install

mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/tmp/kami
cmake --build .

export LD_LIBRARY_PATH=/tmp/kami/lib
./test-bar
./test-cat

```

# Conan Package Manager

This library comes with a `conanfile.py` to build it into a Conan package so that
it may be used by external applications/libraries.

## Create Conan Packages

Creating a Conan package is relatively easy. Simple cd into the source directory
and execute the conan create function.

```bash
git clone https://github.com/GavinNL/cpp_library_template
cd kami

conan create . kami/develop
```

## Using the Conan Package

Once you have created the Conan package, you can then link to it from another
application or library. There are three examples you can look at in the
`test_cmake_install` folder.

* Using [cmake generator](test_cmake_install/conan_cmake_generator)
* Using [cake_paths generator](test_cmake_install/conan_cmake_paths_generator)
* Using [cmake_find_package generator](test_cmake_install/conan_cmake_find_package_generator)
