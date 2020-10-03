####
# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.13)

set(EXAMPLE_NAME "boltzmann2d")

project(${EXAMPLE_NAME}
            LANGUAGES CXX)

find_package(spdlog)

create_executable(  NAME ${EXAMPLE_NAME}
                    SOURCES
                        boltzmann2d.cpp
                    PUBLIC_DEFINITIONS
                        USE_DOUBLE_PRECISION=1
                    PRIVATE_DEFINITIONS
                        DEBUG_VERBOSE
                    PRIVATE_INCLUDE_PATHS
                        ${CMAKE_SOURCE_DIR}/include
                    PUBLIC_LINKED_TARGETS
                        kami
                        spdlog::spdlog
 )

set_target_properties(${EXAMPLE_NAME} PROPERTIES VERSION ${KAMI_VERSION_STRING})

