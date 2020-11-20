####
# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.13)

project(libkamidata  VERSION    ${KAMI_VERSION_STRING}
                     LANGUAGES  CXX)

create_library(NAME         libkamidata
               NAMESPACE    libkamidata
               SOURCES
                   baz.cc
               PUBLIC_INCLUDE_PATHS
                   "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
                   "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated_headers>"
               PRIVATE_LINKED_TARGETS
                   ${COVERAGE_TARGET}
 )

set_target_properties(libkamidata PROPERTIES VERSION        ${KAMI_VERSION_STRING}
                                             SOVERSION      ${KAMI_VERSION_MAJOR}
                                             OUTPUT_NAME    kamidata)

 # Introduce variables:
 # * CMAKE_INSTALL_LIBDIR
 # * CMAKE_INSTALL_BINDIR
 # * CMAKE_INSTALL_INCLUDEDIR
 include(GNUInstallDirs)

 # Headers:
 #   * include/foo/bar/bar.h -> <prefix>/include/NAMESPACE/LIBRARY_NAME/*.h
 #   * include/foo/bar/bar.h -> <prefix>/include/foo/bar/bar.h
 install(
     DIRECTORY   "${CMAKE_SOURCE_DIR}/include/kami/data"
     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/kami"
     FILES_MATCHING PATTERN "*"
 )

add_library(kami::libkamidata ALIAS libkamidata)
