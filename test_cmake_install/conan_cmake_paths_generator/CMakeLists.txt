cmake_minimum_required(VERSION 3.13) # GENERATOR_IS_MULTI_CONFIG

# This requires that the original library provides a Findfoo.cmake file
#
# If you do not want to use the include. you add this via the command line
#  cmake $SRC_FOLDER -DCMAKE_TOOLCHAIN_FILE=$BINARY_FOLDER/conan_paths.cmake
include("${CMAKE_BINARY_DIR}/conan_paths.cmake")

find_package(foo)

add_executable(        test-cat  ../test-cat.cpp)
add_executable(        test-bar  ../test-bar.cpp)

# The target foo::cat is provided by the original CMake installation of
# the library.
target_link_libraries( test-cat  foo::cat)
target_link_libraries( test-bar  foo::bar)
