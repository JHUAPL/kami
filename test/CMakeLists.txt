################################################################################
# This CMakeLists.txt contains the build descriptions for unit tests
################################################################################

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(nlohmann_json 3.11.1 REQUIRED)

file(GLOB test_modules "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")
FOREACH (test_module ${test_modules})
    cmake_path(GET test_module STEM test_src)
    create_test(
            NAME ${test_src}
            SOURCES ${test_src}.cc
            PUBLIC_LINKED_TARGETS gmock gtest kami::libkami Threads::Threads nlohmann_json::nlohmann_json
            COMMAND ${test_src}
            PUBLIC_COMPILE_FEATURES ${COVERAGE_FLAGS}
    )
ENDFOREACH ()
