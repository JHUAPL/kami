################################################################################
# This CMakeLists.txt contains the build descriptions for unit tests
################################################################################

create_test(
        NAME unit-kami-agent
        SOURCES unit-kami-agent.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami
        COMMAND unit-kami-agent
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)

create_test(
        NAME unit-kami-agentid
        SOURCES unit-kami-agentid.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami
        COMMAND unit-kami-agentid
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)

create_test(
        NAME unit-kami-stagedagent
        SOURCES unit-kami-stagedagent.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami
        COMMAND unit-kami-stagedagent
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)
