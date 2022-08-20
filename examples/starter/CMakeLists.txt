####
# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.13)

find_package(spdlog)

set(EXAMPLE_NAME "starter")

project(${EXAMPLE_NAME} LANGUAGES CXX)

create_executable(
        NAME ${EXAMPLE_NAME}
        SOURCES starter.cc
        PUBLIC_DEFINITIONS USE_DOUBLE_PRECISION=1
        PRIVATE_DEFINITIONS DEBUG_VERBOSE
        PRIVATE_INCLUDE_PATHS ${CMAKE_SOURCE_DIR}/include
        PUBLIC_LINKED_TARGETS fmt spdlog::spdlog kami::libkami
)

set_target_properties(${EXAMPLE_NAME} PROPERTIES VERSION ${VERSION_STRING})
