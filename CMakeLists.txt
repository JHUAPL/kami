# This is the Top level CMakelists file which creates the namespace and
# organizes all sublibraries under it.
cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME "kami")

set(VERSION_MAJOR 0)
set(VERSION_MINOR 6)
set(VERSION_PATCH 0)
set(VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

project(${PROJECT_NAME}
        VERSION ${VERSION_STRING}
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_BINARY_DIR}" CACHE STRING "Modules for CMake" FORCE)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(PROJECT_NAMESPACE ${PROJECT_NAME})

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
#  Each example will be built as a static or shared binary and a
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

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

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
    "cmake/config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

#Targets:
#  * <prefix>/lib/libbar.a
#  * <prefix>/lib/libbaz.a
#  * header location after install: <prefix>/include/foo/Bar.hpp
#  * headers can be included by C++ code `#include <foo/Bar.hpp>`
install(
        TARGETS ${sub_modules} ${example_modules} ${COVERAGE_INSTALL_TARGET}
        EXPORT "${TARGETS_EXPORT_NAME}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)


# Config
#   * <prefix>/lib/cmake/Foo/FooConfig.cmake
#   * <prefix>/lib/cmake/Foo/FooConfigVersion.cmake
install(
        FILES "${project_config}" "${version_config}"
        DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooTargets.cmake
install(
        EXPORT "${TARGETS_EXPORT_NAME}"
        NAMESPACE "${namespace}"
        DESTINATION "${config_install_dir}"
)

add_subdirectory(docs)

set(ignoreMe "${CMAKE_C_COMPILER}")
