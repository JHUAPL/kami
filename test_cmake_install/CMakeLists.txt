cmake_minimum_required(VERSION 3.13) # GENERATOR_IS_MULTI_CONFIG

find_package(foo REQUIRED)

add_executable(        test-cat  test-cat.cpp)
target_link_libraries( test-cat  foo::cat)
