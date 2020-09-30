#
# This is the Top level CMakelists file which creates the namespace and
# organizes all sublibraries under it.
#
# The project name in this file is considered the "Namespace"
# and any libraries under it will be given a target of
#
#  Namespace::library_name
#
#
# This Lists file was modified from https://github.com/forexample/package-example
#
# This file creates project 'Foo' with two library targets 'bar' and 'cat'.
# Target 'cat' depends on 'bar'. After installation this project can be found
# by 'find_package(... CONFIG)' command:
#
#    find_package(foo CONFIG REQUIRED)
#    target_link_libraries(... foo::bar)
#
# Note that requirements propagated automatically, for example:
#   * Foo::baz linked automatically
#   * <prefix>/include added to header search path
#   * FOO_BAZ_DEBUG=1/FOO_BAR_DEBUG=1 added on Debug
#   * FOO_BAZ_DEBUG=0/FOO_BAR_DEBUG=0 added on other configurations

####
# Set minimum version of CMake. We need 3.13 at least.
cmake_minimum_required(VERSION 3.13) # GENERATOR_IS_MULTI_CONFIG

set(KAMI_VERSION_MAJOR 0)
set(KAMI_VERSION_MINOR 2)
set(KAMI_VERSION_PATCH 0)
set(KAMI_VERSION_STRING ${KAMI_VERSION_MAJOR}.${KAMI_VERSION_MINOR}.${KAMI_VERSION_PATCH})

################################################################################
# Set variables for the project. The:
#   * PROJECT_NAME
#   * PROJECT_VERSION
#   * PROJECT_NAMESPACE should be the same as the project.
project(kami  VERSION       ${KAMI_VERSION_STRING}
              LANGUAGES     CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(PROJECT_NAMESPACE        kami  )  # The project namespace. Library targets
                                      # will be referred by
                                      # foo::bar. This value should usually be
                                      # the same as the project.
################################################################################





if(CMAKE_COMPILER_IS_GNUCC)
    option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

################################################################################
# If coverage reporting is turned on. Create a custom target so that
# the libraries can link to it to acquire the appropriate flags.
#
# Also generate a custom target `gcov` so that the coverage reports can be created
################################################################################
if(ENABLE_COVERAGE)
    include(cmake/coverage.cmake)
endif()

include(cmake/functions.cmake)
include(cmake/warnings.cmake)
include(cmake/cppcheck.cmake)

################################################################################
# Sub libraries.
#
#  Each sub library will be built as a static or shared library and a
#  target will be created for it.
################################################################################

directory_list(sub_modules "${CMAKE_CURRENT_SOURCE_DIR}/src")

FOREACH(subdir ${sub_modules})
    add_subdirectory(src/${subdir})
ENDFOREACH()

################################################################################


################################################################################
# Examples.
#
#  Each example will be built as a static or shared library and a
#  target will be created for it.
################################################################################

directory_list(example_modules "${CMAKE_CURRENT_SOURCE_DIR}/examples")

FOREACH(subdir ${example_modules})
    add_subdirectory(examples/${subdir})
ENDFOREACH()

################################################################################

enable_testing()
add_subdirectory(test)

################################################################################
# Installation of the library and all it's sub components. No need to edit this.
################################################################################
# Get the Default installation folders:
# * CMAKE_INSTALL_LIBDIR
# * CMAKE_INSTALL_BINDIR
# * CMAKE_INSTALL_INCLUDEDIR
include(GNUInstallDirs)

# Layout. This works for all platforms:
#   * <prefix>/lib*/cmake/<PROJECT-NAME>
#   * <prefix>/lib*/
#   * <prefix>/include/
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

set(generated_dir                "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Use:
#   * PROJECT_VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * TARGETS_EXPORT_NAME
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

#Targets:
#  * <prefix>/lib/libbar.a
#  * <prefix>/lib/libbaz.a
#  * header location after install: <prefix>/include/foo/Bar.hpp
#  * headers can be included by C++ code `#include <foo/Bar.hpp>`
  install(
   TARGETS
       ${sub_modules} ${example_modules}
       ${COVERAGE_INSTALL_TARGET}
   EXPORT
       "${TARGETS_EXPORT_NAME}"
   LIBRARY  DESTINATION "${CMAKE_INSTALL_LIBDIR}"
   ARCHIVE  DESTINATION "${CMAKE_INSTALL_LIBDIR}"
   RUNTIME  DESTINATION "${CMAKE_INSTALL_BINDIR}"
   INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  )


# Config
#   * <prefix>/lib/cmake/Foo/FooConfig.cmake
#   * <prefix>/lib/cmake/Foo/FooConfigVersion.cmake
install(
    FILES
        "${project_config}" "${version_config}"
    DESTINATION
        "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooTargets.cmake
install(
    EXPORT
        "${TARGETS_EXPORT_NAME}"
    NAMESPACE
        "${namespace}"
    DESTINATION
        "${config_install_dir}"
)

add_subdirectory(docs)