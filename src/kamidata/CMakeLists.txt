####
# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.13)

project(libkamidata  VERSION    ${KAMI_VERSION_STRING}
                     LANGUAGES  CXX)

create_library(NAME  kamidata
               NAMESPACE kamidata
               SOURCES
                   baz.cc
               PUBLIC_INCLUDE_PATHS
                   "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
                   "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated_headers>"
               PRIVATE_LINKED_TARGETS
                   ${COVERAGE_TARGET}
               EXPORT_FILE_PATH
                   "${CMAKE_CURRENT_BINARY_DIR}/generated_headers/kami/data/KAMIDATA_EXPORT.h"
 )
 
set_target_properties(kamidata PROPERTIES VERSION ${KAMI_VERSION_STRING}
                                        SOVERSION ${KAMI_VERSION_MAJOR})

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
     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/kami/data"
     FILES_MATCHING PATTERN "*"
 )

 # Export headers:
 #   The export header will be stored in:
 #            <prefix>/include/${NAMESPACE}/LIBRARY_NAME/LIBRARY_NAME_export.h
 install(
     FILES
         "${CMAKE_CURRENT_BINARY_DIR}/generated_headers/kami/data/KAMIDATA_EXPORT.h"
     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/kami/data"
 )

add_library(kami::data ALIAS kamidata)

################################################################################

# }
