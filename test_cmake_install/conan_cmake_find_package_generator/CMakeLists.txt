cmake_minimum_required(VERSION 3.13) # GENERATOR_IS_MULTI_CONFIG

list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR}" CACHE STRING "Modules for CMake" FORCE)

find_package(foo)

add_executable(        test-cat  ../test-cat.cpp)
add_executable(        test-bar  ../test-bar.cpp)

# Here foo::foo is defined by the libraries
# listed in the conan file. foo::foo is not defined by
# the normal cmake installation.
target_link_libraries( test-cat  foo::foo)
target_link_libraries( test-bar  foo::foo)
