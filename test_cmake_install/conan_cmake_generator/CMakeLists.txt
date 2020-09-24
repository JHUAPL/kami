cmake_minimum_required(VERSION 3.13) # GENERATOR_IS_MULTI_CONFIG

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(        test-cat  ../test-cat.cpp)
add_executable(        test-bar  ../test-bar.cpp)

# The values of CONAN_PKG::foo are set by
# the conanfile.py file
target_link_libraries( test-cat  CONAN_PKG::foo)
target_link_libraries( test-bar  CONAN_PKG::foo)
