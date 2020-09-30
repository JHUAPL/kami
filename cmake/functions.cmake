include(GenerateExportHeader)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

MACRO(directory_list result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child} )
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

MACRO(print_list result)
    foreach(arg IN LISTS ${result})
        message(" - ${arg}")
    endforeach()
ENDMACRO()


MACRO(print_list_label Label ListVar)
    message("${Label}:")
    print_list(${ListVar})
ENDMACRO()


# create_library(  NAME myLibrary
#                  NAMESPACE myNamespace
#                  SOURCES
#                       myLib.cpp
#                       myLib_functions.cpp
#                  PUBLIC_DEFINITIONS
#                     USE_DOUBLE_PRECISION=1
#                  PRIVATE_DEFINITIONS
#                     DEBUG_VERBOSE
#                  PUBLIC_INCLUDE_PATHS
#                     ${CMAKE_SOURCE_DIR}/mylib/include
#                  PRIVATE_INCLUDE_PATHS
#                     ${CMAKE_SOURCE_DIR}/include
#                  PRIVATE_LINKED_TARGETS
#                     Threads::Threads
#                  PUBLIC_LINKED_TARGETS
#                     Threads::Threads
#                  LINKED_TARGETS
#                     Threads::Threads
#                  EXPORT_FILE_PATH
#                      ${CMAKE_BINARY_DIR}/MYLIBRARY_EXPORT.h

################################################################################
# Create a Library.
#
# Example usage:
#
# create_library(  NAME myLibrary
#                  NAMESPACE myNamespace
#                  SOURCES
#                       myLib.cpp
#                       myLib_functions.cpp
#                  PUBLIC_DEFINITIONS
#                     USE_DOUBLE_PRECISION=1
#                  PRIVATE_DEFINITIONS
#                     DEBUG_VERBOSE
#                  PUBLIC_INCLUDE_PATHS
#                     ${CMAKE_SOURCE_DIR}/mylib/include
#                  PRIVATE_INCLUDE_PATHS
#                     ${CMAKE_SOURCE_DIR}/include
#                  PRIVATE_LINKED_TARGETS
#                     Threads::Threads
#                  PUBLIC_LINKED_TARGETS
#                     Threads::Threads
#                  LINKED_TARGETS
#                     Threads::Threads
#                  EXPORT_FILE_PATH
#                      ${CMAKE_BINARY_DIR}/MYLIBRARY_EXPORT.h
# )
#
# The above example creates an alias target, myNamespace::myLibrary which can be
# linked to by other tar gets.
# PUBLIC_DEFINITIONS -  preprocessor defines which are inherated by targets which
#                       link to this library
#
# PRIVATE_DEFINITIONS - preprocessor defines which are private and only seen by
#                       myLibrary
#
# PUBLIC_INCLUDE_PATHS - include paths which are public, therefore inherted by
#                        targest which link to this library.
#
# PRIVATE_INCLUDE_PATHS - private include paths which are only visible by MyLibrary
#
# LINKED_TARGETS        - targets to link to.
#
# EXPORT_FILE_PATH      - the export file to generate for dll files.
################################################################################
function(create_library)
    set(options)
    set(args NAME
             NAMESPACE
             EXPORT_FILE_PATH
             )

    set(list_args
            PUBLIC_LINKED_TARGETS
            PRIVATE_LINKED_TARGETS
            SOURCES
            PUBLIC_DEFINITIONS
            PRIVATE_DEFINITIONS
            PUBLIC_INCLUDE_PATHS
            PRIVATE_INCLUDE_PATHS
            PUBLIC_COMPILE_FEATURES
            PRIVATE_COMPILE_FEATURES
            PUBLIC_COMPILE_OPTIONS
            PRIVATE_COMPILE_OPTIONS
        )

    cmake_parse_arguments(
        PARSE_ARGV 0
        lib
        "${options}"
        "${args}"
        "${list_args}"
    )

    message("--------------------------")
    message("Creating Library")
    if("${lib_NAME}" STREQUAL "")
        get_filename_component(lib_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
        string(REPLACE " " "_" lib_NAME ${lib_NAME})
        message(" Library, NAME argument not provided. Using folder name:  ${lib_NAME}")
    endif()

    if("${lib_NAMESPACE}" STREQUAL "")
        set(lib_NAMESPACE ${lib_NAME})
        message(" Library, NAMESPACE argument not provided. Using target alias:  ${lib_NAME}::${lib_NAME}")
    endif()


    message("-----------------------------------")
    message("Building Library:        ${lib_NAME}")
    message("-----------------------------------")
    print_list_label("Sources" lib_SOURCES)
    print_list_label("Public Linked Targest"  lib_PUBLIC_LINKED_TARGETS)
    print_list_label("Private Linked Targest"  lib_PRIVATE_LINKED_TARGETS)
    print_list_label("Public Include Paths"  lib_PUBLIC_INCLUDE_PATHS)
    print_list_label("Private Include Paths" lib_PRIVATE_INCLUDE_PATHS)
    print_list_label("Public Compile Features" lib_PUBLIC_COMPILE_FEATURES)
    print_list_label("Private Compile Features" lib_PRIVATE_COMPILE_FEATURES)
    print_list_label("Public Definitions" lib_PUBLIC_DEFINITIONS)
    print_list_label("Private Definitions" lib_PRIVATE_DEFINITIONS)
    message("Export File Name:")
    message(" - ${lib_EXPORT_FILE_PATH}")
    message("-----------------------------------")

    add_library( ${lib_NAME} ${lib_SOURCES} )
    add_library( ${lib_NAMESPACE}::${lib_NAME}  ALIAS  ${lib_NAME}   )

    target_compile_features(${lib_NAME} PUBLIC ${lib_PUBLIC_COMPILE_FEATURES} )
    target_compile_features(${lib_NAME} PRIVATE ${lib_PRIVATE_COMPILE_FEATURES} )

    target_compile_options(${lib_NAME} PUBLIC ${lib_PUBLIC_COMPILE_OPTIONS} )
    target_compile_options(${lib_NAME} PRIVATE ${lib_PRIVATE_COMPILE_OPTIONS} )

    target_link_libraries( ${lib_NAME} PUBLIC ${lib_PUBLIC_LINKED_TARGETS})
    target_link_libraries( ${lib_NAME} PRIVATE ${lib_PRIVATE_LINKED_TARGETS})

    target_include_directories( ${lib_NAME}
                                PUBLIC
                                    ${lib_INCLUDE_PATHS}
                                    ${lib_PUBLIC_INCLUDE_PATHS}
                                PRIVATE
                                    ${lib_PRIVATE_INCLUDE_PATHS}
                                )

    target_compile_definitions( ${lib_NAME}
                                PUBLIC
                                    ${lib_PUBLIC_DEFINITIONS}
                                PRIVATE
                                    ${lib_PRIVATE_DEFINITIONS}
                               )

    if( NOT "${lib_EXPORT_FILE_PATH}" STREQUAL "" )
        generate_export_header( ${lib_NAME}
                                EXPORT_FILE_NAME
                                    ${lib_EXPORT_FILE_PATH}
                            )
    endif()


################################################################################
# Debug Information Format:
# * https://docs.microsoft.com/en-us/cpp/build/reference/z7-zi-zi-debug-information-format
#
# Notes:
#
# * /Z7 still produce PDB file for DLL and without the PDB file installed
#   you can't debug DLL
#
# * /Z7 for static library doesn't produce PDB. It's the best option if you
#   want debug library without changing internal CMake code.
#   Toolchain example: https://github.com/ruslo/polly/blob/master/vs-15-2017-win64-z7.cmake
#
# * /Zi option is default (produce separate PDB files)
#
# * TARGET_PDB_FILE generator expression doesn't support static libraries.
#   See https://gitlab.kitware.com/cmake/cmake/issues/16932
#   (that's why it's not used here)
#
# * This code can be implemented as a 'PDB DESTINATION' feature.
#   See https://gitlab.kitware.com/cmake/cmake/issues/16935#note_275180
#
# * By default only Debug/RelWithDebInfo produce debug information,
#   Release/MinSizeRel do not.
#
# * Generated PDB for static libraries doesn't respect CMAKE_<CONFIG>_POSTFIX
#   variable. It means if you specify Debug and RelWithDebInfo then generated
#   PDB files for both will be "md5.pdb". When PDB files installed one will
#   overwrite another making it unusable. Release + Debug configurations will
#   work fine because Release doesn't produce PDB files.
#
# * All PDB files will be installed, including PDB for targets that will not
#   be installed themselves.
################################################################################
    if(MSVC)
      set(pdb_output_dir "${CMAKE_CURRENT_BINARY_DIR}/pdb-files")

      set(CMAKE_PDB_OUTPUT_DIRECTORY "${pdb_output_dir}")
      set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY "${pdb_output_dir}")

      get_cmake_property(is_multi GENERATOR_IS_MULTI_CONFIG)
      if(is_multi)
        set(config_suffix "$<CONFIG>")
      else()
        set(config_suffix "")
      endif()

      # Introduce variables:
      # * CMAKE_INSTALL_LIBDIR
      # * CMAKE_INSTALL_BINDIR
      include(GNUInstallDirs)

      if(BUILD_SHARED_LIBS)
        set(pdb_dst ${CMAKE_INSTALL_BINDIR})
      else()
        set(pdb_dst ${CMAKE_INSTALL_LIBDIR})
      endif()

      install(
          DIRECTORY "${pdb_output_dir}/${config_suffix}/"
          DESTINATION ${pdb_dst}
      )
    endif()
################################################################################

    foreach(arg IN LISTS lib_UNPARSED_ARGUMENTS)
        message(WARNING "Unparsed argument: ${arg}")
    endforeach()

endfunction()



################################################################################
# Create an executable.
#
# Example usage:
#
# create_executable(  NAME myExe
#                  SOURCES
#                       main.cpp
#                  PUBLIC_DEFINITIONS
#                     USE_DOUBLE_PRECISION=1
#                  PRIVATE_DEFINITIONS
#                     DEBUG_VERBOSE
#                  PUBLIC_INCLUDE_PATHS
#                     ${CMAKE_SOURCE_DIR}/mylib/include
#                  PRIVATE_INCLUDE_PATHS
#                     ${CMAKE_SOURCE_DIR}/include
#                  PRIVATE_LINKED_TARGETS
#                     Threads::Threads
#                  PUBLIC_LINKED_TARGETS
#                     Threads::Threads
#                  LINKED_TARGETS
#                     Threads::Threads
#                     myNamespace::myLib
# )
#
# The above example creates an alias target, myNamespace::myLibrary which can be
# linked to by other tar gets.
# PUBLIC_DEFINITIONS -  preprocessor defines which are inherated by targets which
#                       link to this library
#
# PRIVATE_DEFINITIONS - preprocessor defines which are private and only seen by
#                       myLibrary
#
# PUBLIC_INCLUDE_PATHS - include paths which are public, therefore inherted by
#                        targest which link to this library.
#
# PRIVATE_INCLUDE_PATHS - private include paths which are only visible by MyExe
#
# LINKED_TARGETS        - targets to link to.
################################################################################

function(create_executable)
    set(options)
    set(args NAME
             )

     set(list_args
             PUBLIC_LINKED_TARGETS
             PRIVATE_LINKED_TARGETS
             SOURCES
             PUBLIC_DEFINITIONS
             PRIVATE_DEFINITIONS
             PUBLIC_INCLUDE_PATHS
             PRIVATE_INCLUDE_PATHS
             PUBLIC_COMPILE_FEATURES
             PRIVATE_COMPILE_FEATURES
             PUBLIC_COMPILE_OPTIONS
             PRIVATE_COMPILE_OPTIONS
         )

    cmake_parse_arguments(
        PARSE_ARGV 0
        lib
        "${options}"
        "${args}"
        "${list_args}"
    )
    message("-----------------------------------")
    message("Building Executable:      ${Green}${lib_NAME}${ColourReset}")
    message("-----------------------------------")
    print_list_label("Sources" lib_SOURCES)
    print_list_label("Public Linked Targest"  lib_PUBLIC_LINKED_TARGETS)
    print_list_label("Private Linked Targest"  lib_PRIVATE_LINKED_TARGETS)
    print_list_label("Public Include Paths"  lib_PUBLIC_INCLUDE_PATHS)
    print_list_label("Private Include Paths" lib_PRIVATE_INCLUDE_PATHS)
    print_list_label("Public Compile Features" lib_PUBLIC_COMPILE_FEATURES)
    print_list_label("Private Compile Features" lib_PRIVATE_COMPILE_FEATURES)
    print_list_label("Public Definitions" lib_PUBLIC_DEFINITIONS)
    print_list_label("Private Definitions" lib_PRIVATE_DEFINITIONS)
    message("Export File Name:")
    message(" - ${lib_EXPORT_FILE_PATH}")
    message("-----------------------------------")
    add_executable( ${lib_NAME} ${lib_SOURCES} )
    target_link_libraries( ${lib_NAME} PUBLIC ${lib_PUBLIC_LINKED_TARGETS} )



    target_include_directories( ${lib_NAME}
                                PUBLIC
                                    ${lib_PUBLIC_INCLUDE_PATHS}
                                PRIVATE
                                    ${lib_PRIVATE_INCLUDE_PATHS}
                                )

    target_compile_definitions( ${lib_NAME}
                                PUBLIC
                                    ${lib_PUBLIC_DEFINITIONS}
                                PRIVATE
                                    ${lib_PRIVATE_DEFINITIONS}
                               )

    target_compile_features(${lib_NAME} PUBLIC ${lib_PUBLIC_COMPILE_FEATURES} )
    target_compile_features(${lib_NAME} PRIVATE ${lib_PRIVATE_COMPILE_FEATURES} )

    target_compile_options(${lib_NAME} PUBLIC ${lib_PUBLIC_COMPILE_OPTIONS} )
    target_compile_options(${lib_NAME} PRIVATE ${lib_PRIVATE_COMPILE_OPTIONS} )

################################################################################

    foreach(arg IN LISTS lib_UNPARSED_ARGUMENTS)
        message(WARNING "Unparsed argument: ${arg}")
    endforeach()

endfunction(create_executable)



function(create_module)
    set(options)
    set(args NAME
             )

    set(list_args
            LINKED_TARGETS
            SOURCES
            PUBLIC_DEFINITIONS
            PRIVATE_DEFINITIONS
            INCLUDE_PATHS)

    cmake_parse_arguments(
        PARSE_ARGV 0
        lib
        "${options}"
        "${args}"
        "${list_args}"
    )
    message("Building Module: ${lib_NAME}")

    add_library( ${lib_NAME} MODULE ${lib_SOURCES} )

    target_link_libraries( ${lib_NAME} PUBLIC ${lib_LINKED_TARGETS} )
    set_target_properties( ${lib_NAME} PROPERTIES SUFFIX ".so")
    set_target_properties( ${lib_NAME} PROPERTIES PREFIX "")

    target_include_directories( ${lib_NAME}
                                PUBLIC
                                    ${lib_INCLUDE_PATHS}
                                    ${lib_PUBLIC_INCLUDE_PATHS}
                                PRIVATE
                                    ${lib_PRIVATE_INCLUDE_PATHS}
                                )

    target_compile_definitions( ${lib_NAME}
                                PUBLIC
                                    ${lib_PUBLIC_DEFINITIONS}
                                PRIVATE
                                    ${lib_PRIVATE_DEFINITIONS}
                               )

################################################################################

    foreach(arg IN LISTS lib_UNPARSED_ARGUMENTS)
        message(WARNING "Unparsed argument: ${arg}")
    endforeach()

endfunction()



################################################################################
# Create a Header Only Library.
#
# Example usage:
#
# create_library(  NAME myLibrary
#                  NAMESPACE myNamespace
#                  SOURCES
#                       myLib.cpp
#                       myLib_functions.cpp
#                  PUBLIC_DEFINITIONS
#                     USE_DOUBLE_PRECISION=1
#                  PRIVATE_DEFINITIONS
#                     DEBUG_VERBOSE
#                  PUBLIC_INCLUDE_PATHS
#                     ${CMAKE_SOURCE_DIR}/mylib/include
#                  PRIVATE_INCLUDE_PATHS
#                     ${CMAKE_SOURCE_DIR}/include
#                  PRIVATE_LINKED_TARGETS
#                     Threads::Threads
#                  PUBLIC_LINKED_TARGETS
#                     Threads::Threads
#                  LINKED_TARGETS
#                     Threads::Threads
#                  EXPORT_FILE_PATH
#                      ${CMAKE_BINARY_DIR}/MYLIBRARY_EXPORT.h
# )
#
# The above example creates an alias target, myNamespace::myLibrary which can be
# linked to by other tar gets.
# PUBLIC_DEFINITIONS -  preprocessor defines which are inherated by targets which
#                       link to this library
#
# PRIVATE_DEFINITIONS - preprocessor defines which are private and only seen by
#                       myLibrary
#
# PUBLIC_INCLUDE_PATHS - include paths which are public, therefore inherted by
#                        targest which link to this library.
#
# PRIVATE_INCLUDE_PATHS - private include paths which are only visible by MyLibrary
#
# LINKED_TARGETS        - targets to link to.
#
# EXPORT_FILE_PATH      - the export file to generate for dll files.
################################################################################
function(create_header_only_library)
    set(options)
    set(args NAME
             NAMESPACE
             )

    set(list_args
            PUBLIC_LINKED_TARGETS
            PRIVATE_LINKED_TARGETS
            SOURCES
            PUBLIC_DEFINITIONS
            PRIVATE_DEFINITIONS
            PUBLIC_INCLUDE_PATHS
            PRIVATE_INCLUDE_PATHS
            PUBLIC_COMPILE_FEATURES
            PRIVATE_COMPILE_FEATURES
            PUBLIC_COMPILE_OPTIONS
            PRIVATE_COMPILE_OPTIONS
        )

    cmake_parse_arguments(
        PARSE_ARGV 0
        lib
        "${options}"
        "${args}"
        "${list_args}"
    )

    message("--------------------------")
    message("Creating Header-Only Library")
    if("${lib_NAME}" STREQUAL "")
        get_filename_component(lib_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
        string(REPLACE " " "_" lib_NAME ${lib_NAME})
        message(" Library, NAME argument not provided. Using folder name:  ${lib_NAME}")
    endif()

    if("${lib_NAMESPACE}" STREQUAL "")
        set(lib_NAMESPACE ${lib_NAME})
        message(" Library, NAMESPACE argument not provided. Using target alias:  ${lib_NAME}::${lib_NAME}")
    endif()


    message("-----------------------------------")
    message("Building Library:        ${lib_NAME}   Alias: ${lib_NAMESPACE}::${lib_NAME}")
    message("-----------------------------------")
    print_list_label("Sources" lib_SOURCES)
    print_list_label("Public Linked Targest"  lib_PUBLIC_LINKED_TARGETS)
    print_list_label("Private Linked Targest"  lib_PRIVATE_LINKED_TARGETS)
    print_list_label("Public Include Paths"  lib_PUBLIC_INCLUDE_PATHS)
    print_list_label("Private Include Paths" lib_PRIVATE_INCLUDE_PATHS)
    print_list_label("Public Compile Features" lib_PUBLIC_COMPILE_FEATURES)
    print_list_label("Private Compile Features" lib_PRIVATE_COMPILE_FEATURES)
    print_list_label("Public Definitions" lib_PUBLIC_DEFINITIONS)
    print_list_label("Private Definitions" lib_PRIVATE_DEFINITIONS)
    message("Export File Name:")
    message(" - ${lib_EXPORT_FILE_PATH}")
    message("-----------------------------------")

    add_library( ${lib_NAME} INTERFACE ${lib_SOURCES} )
    add_library( ${lib_NAMESPACE}::${lib_NAME}  ALIAS  ${lib_NAME}   )

    target_compile_features(${lib_NAME} INTERFACE ${lib_PUBLIC_COMPILE_FEATURES} )
    target_compile_features(${lib_NAME} INTERFACE ${lib_PRIVATE_COMPILE_FEATURES} )

    target_compile_features(${lib_NAME} INTERFACE ${lib_PUBLIC_COMPILE_OPTIONS} )
    target_compile_features(${lib_NAME} INTERFACE ${lib_PRIVATE_COMPILE_OPTIONS} )

    target_link_libraries( ${lib_NAME} PUBLIC ${PUBLIC_LINKED_TARGETS})
    target_link_libraries( ${lib_NAME} PRIVATE ${PRIVATE_LINKED_TARGETS})

    target_include_directories( ${lib_NAME}
                                INTERFACE
                                    ${lib_PUBLIC_INCLUDE_PATHS}
                                    ${lib_PRIVATE_INCLUDE_PATHS}
                                )

    target_compile_definitions( ${lib_NAME}
                                INTERFACE
                                    ${lib_PUBLIC_DEFINITIONS}
                                    ${lib_PRIVATE_DEFINITIONS}
                               )

    foreach(arg IN LISTS lib_UNPARSED_ARGUMENTS)
        message(WARNING "Unparsed argument: ${arg}")
    endforeach()

endfunction()



function(create_test)
    set(options)
    set(args NAME
             WORKING_DIRECTORY
             )

    set(list_args
            PUBLIC_LINKED_TARGETS
            PRIVATE_LINKED_TARGETS
            SOURCES
            COMMAND
            PUBLIC_DEFINITIONS
            PRIVATE_DEFINITIONS
            PUBLIC_INCLUDE_PATHS
            PRIVATE_INCLUDE_PATHS
            PUBLIC_COMPILE_FEATURES
            PRIVATE_COMPILE_FEATURES
        )

    cmake_parse_arguments(
        PARSE_ARGV 0
        lib
        "${options}"
        "${args}"
        "${list_args}"
    )


    message("-----------------------------------")
    message("Building Test:        ${lib_NAME} ")
    message("-----------------------------------")
    message("Command to Execute: ${lib_COMMAND}")
    message("Working Directory : ${lib_WORKING_DIRECTORY}")
    print_list_label("Sources" lib_SOURCES)
    print_list_label("Public Linked Targest"  lib_PUBLIC_LINKED_TARGETS)
    print_list_label("Private Linked Targest"  lib_PRIVATE_LINKED_TARGETS)
    print_list_label("Public Include Paths"  lib_PUBLIC_INCLUDE_PATHS)
    print_list_label("Private Include Paths" lib_PRIVATE_INCLUDE_PATHS)
    print_list_label("Public Compile Features" lib_PUBLIC_COMPILE_FEATURES)
    print_list_label("Private Compile Features" lib_PRIVATE_COMPILE_FEATURES)
    print_list_label("Public Definitions" lib_PUBLIC_DEFINITIONS)
    print_list_label("Private Definitions" lib_PRIVATE_DEFINITIONS)
    message("Export File Name:")
    message(" - ${lib_EXPORT_FILE_PATH}")
    message("-----------------------------------")


    set(testcase ${lib_NAME} )

    add_executable(${testcase} ${lib_SOURCES})
    target_compile_definitions(${testcase} PRIVATE
      #CATCH_CONFIG_FAST_COMPILE
      $<$<CXX_COMPILER_ID:MSVC>:_SCL_SECURE_NO_WARNINGS>
      ${lib_PRIVATE_DEFINITIONS}
      ${lib_PUBLIC_DEFINITIONS}
    )
    target_compile_options(${testcase} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/EHsc;$<$<CONFIG:Release>:/Od>>
       # $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wno-deprecated;-Wno-float-equal>
        $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-declarations>
        ${lib_PUBLIC_COMPILE_FEATURES}
        ${lib_PRIVATE_COMPILE_FEATURES}
    )
    target_include_directories(${testcase} PRIVATE
        ${lib_PUBLIC_INCLUDE_PATHS}
        ${lib_PRIVATE_INCLUDE_PATHS}
    )

    target_link_libraries(${testcase} ${lib_PUBLIC_LINKED_TARGETS} ${lib_PRIVATE_LINKED_TARGETS} )
    #target_link_libraries(${testcase} --coverage -g -O0 -fprofile-arcs -ftest-coverage)
    #target_compile_options(${testcase} PRIVATE --coverage -g -O0 -fprofile-arcs -ftest-coverage)

    #MESSAGE("         Adding link libraries for ${testcase}: ${GNL_LIBS}  ${GNL_COVERAGE_FLAGS} ")

    add_test( NAME ${testcase}
              COMMAND ${lib_COMMAND}
              WORKING_DIRECTORY ${lib_WORKING_DIRECTORY})

endfunction()
