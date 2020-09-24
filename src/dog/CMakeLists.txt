####
# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.13)

project(dog  VERSION  1.2.3)

create_library(NAME  dog
               NAMESPACE foo
               SOURCES
                   dog.cpp
               PUBLIC_LINKED_TARGETS
                   foo::cat foo::bar
               PRIVATE_LINKED_TARGETS
                   ${COVERAGE_TARGET}
               PUBLIC_INCLUDE_PATHS
                   "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
                   "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated_headers>"
               EXPORT_FILE_PATH
                   "${CMAKE_CURRENT_BINARY_DIR}/generated_headers/foo/dog/DOG_EXPORT.h"
 )


 # Introduce variables:
 # * CMAKE_INSTALL_LIBDIR
 # * CMAKE_INSTALL_BINDIR
 # * CMAKE_INSTALL_INCLUDEDIR
 include(GNUInstallDirs)

 # Headers:
 #   * include/foo/bar/bar.h -> <prefix>/include/NAMESPACE/LIBRARY_NAME/*.h
 #   * include/foo/bar/bar.h -> <prefix>/include/foo/bar/bar.h
 install(
     DIRECTORY   "${CMAKE_SOURCE_DIR}/include/foo/dog"
     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/foo/"
     FILES_MATCHING PATTERN "*"
 )

 # Export headers:
 #   The export header will be stored in:
 #            <prefix>/include/${NAMESPACE}/LIBRARY_NAME/LIBRARY_NAME_export.h
 install(
     FILES
         "${CMAKE_CURRENT_BINARY_DIR}/generated_headers/foo/dog/DOG_EXPORT.h"
     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/foo/dog"
 )

################################################################################

# }
