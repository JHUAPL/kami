################################################################################
# This CMakeLists.txt contains the build descriptions for unit tests
################################################################################

cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

create_test( NAME  test-foo.cat        # Name for the unit test
               SOURCES                    # The sources that will be compiled [optional]
                    unit-foo.cat.cpp
               PUBLIC_LINKED_TARGETS              # The targest that need to be linked to this unit test [optional]
                    foo::cat
                    ${COVERAGE_LIBS}
               COMMAND                   # The command to be called.
                    test-foo.cat
               PUBLIC_COMPILE_FEATURES
                    ${COVERAGE_FLAGS}
               )

create_test( NAME  test-foo.bar        # Name for the unit test
             SOURCES                    # The sources that will be compiled [optional]
               unit-foo.bar.cpp
             PUBLIC_LINKED_TARGETS              # The targest that need to be linked to this unit test [optional]
               foo::bar
               ${COVERAGE_LIBS}
             COMMAND                   # The command to be called.
               test-foo.bar
             PUBLIC_COMPILE_FEATURES
               ${COVERAGE_FLAGS}
             )
