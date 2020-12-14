################################################################################
# This CMakeLists.txt contains the build descriptions for unit tests
################################################################################

cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

find_package(spdlog)

create_test( NAME
                unit-kami-agentid
             SOURCES
                unit-kami-agentid.cc
             PUBLIC_LINKED_TARGETS
                kami::libkami
                fmt
                spdlog::spdlog
                ${COVERAGE_LIBS}
             COMMAND
                unit-kami-agentid
             PUBLIC_COMPILE_FEATURES
                ${COVERAGE_FLAGS})

create_test( NAME
                unit-kami-agent
             SOURCES
                unit-kami-agent.cc
             PUBLIC_LINKED_TARGETS
                kami::libkami
                fmt
                spdlog::spdlog
                ${COVERAGE_LIBS}
             COMMAND
                unit-kami-agent
             PUBLIC_COMPILE_FEATURES
                ${COVERAGE_FLAGS})
