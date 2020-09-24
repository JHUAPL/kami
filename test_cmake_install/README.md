# Test CMake Install

This tests whether the find_package(foo) works properly after the library has
been installed.

To do this, we first have to build the main library and install it into a
temporary location.

```Bash
# Build the main library and install it into /tmp/cpp_library_template
cd cpp_library_template
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/tmp/cpp_library_template -DBUILD_SHARED_LIBS:BOOL=TRUE
cmake --build .
cmake --build . --target install

# Delete the build directory to make sure we don't accidentally link to the build
# folder instead.
cd ..
rm -rf build

# Build the test library and point the CMAKE_PREFIX_PATH to the location we
# installed the library to.
cd test_cmake_install/cmake
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/tmp/cpp_library_template
cmake --build .

```

Because we installed the libary to a non-standard location, we will need to
set the LD_LIBRARY_PATH env variable before we are able to run the two executables
we created

```Bash
export LD_LIBRARY_PATH=/tmp/cpp_library_template/lib

./test-bar
./test-cat

```
