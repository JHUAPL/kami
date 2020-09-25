################################################################################
# This CMakeLists.txt contains the build descriptions for unit tests
################################################################################

cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

create_test( NAME  
                unit-kami-agentid
             SOURCES
                unit-kami-agentid.cpp
             PUBLIC_LINKED_TARGETS
                kami::kami
                ${COVERAGE_LIBS}
             COMMAND
                unit-kami-agentid
             PUBLIC_COMPILE_FEATURES
                ${COVERAGE_FLAGS})

create_test( NAME  
                unit-kami-agent
             SOURCES
                unit-kami-agent.cpp
             PUBLIC_LINKED_TARGETS
                kami::kami
                ${COVERAGE_LIBS}
             COMMAND
                unit-kami-agent
             PUBLIC_COMPILE_FEATURES
                ${COVERAGE_FLAGS})
