add_custom_target(cppcheck
    #COMMAND mkdir -p coverage
    #COMMAND ${CMAKE_MAKE_PROGRAM} test
    #WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET cppcheck
    COMMAND echo "=================== CPPCHECK ===================="
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/cppcheck
    COMMAND cppcheck . -I include/ --enable=all --inconclusive --xml-version=2 --force --library=windows,posix,gnu . --output-file=${CMAKE_BINARY_DIR}/cppcheck/result.xml
    COMMAND cppcheck-htmlreport --source-encoding="iso8859-1" --title="mmp2top" --source-dir . --report-dir=${CMAKE_BINARY_DIR}/cppcheck --file=${CMAKE_BINARY_DIR}/cppcheck/result.xml
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}  # Need separate command for this line
    )
