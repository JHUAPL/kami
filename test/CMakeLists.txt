################################################################################
# This CMakeLists.txt contains the build descriptions for unit tests
################################################################################

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

create_test(
        NAME unit-kami-agent
        SOURCES unit-kami-agent.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami Threads::Threads
        COMMAND unit-kami-agent
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)

create_test(
        NAME unit-kami-agentid
        SOURCES unit-kami-agentid.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami Threads::Threads
        COMMAND unit-kami-agentid
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)

create_test(
        NAME unit-kami-gridcoord1d
        SOURCES unit-kami-gridcoord1d.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami Threads::Threads
        COMMAND unit-kami-gridcoord1d
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)

create_test(
        NAME unit-kami-gridcoord2d
        SOURCES unit-kami-gridcoord2d.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami Threads::Threads
        COMMAND unit-kami-gridcoord2d
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)

create_test(
        NAME unit-kami-model
        SOURCES unit-kami-model.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami Threads::Threads
        COMMAND unit-kami-model
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)

create_test(
        NAME unit-kami-multigrid1d
        SOURCES unit-kami-multigrid1d.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami Threads::Threads
        COMMAND unit-kami-multigrid1d
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)

create_test(
        NAME unit-kami-multigrid2d
        SOURCES unit-kami-multigrid2d.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami Threads::Threads
        COMMAND unit-kami-multigrid2d
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)

create_test(
        NAME unit-kami-sologrid1d
        SOURCES unit-kami-sologrid1d.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami Threads::Threads
        COMMAND unit-kami-sologrid1d
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)

create_test(
        NAME unit-kami-sologrid2d
        SOURCES unit-kami-sologrid2d.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami Threads::Threads
        COMMAND unit-kami-sologrid2d
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)

create_test(
        NAME unit-kami-stagedagent
        SOURCES unit-kami-stagedagent.cc
        PUBLIC_LINKED_TARGETS gmock gtest kami::libkami Threads::Threads
        COMMAND unit-kami-stagedagent
        PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
)
