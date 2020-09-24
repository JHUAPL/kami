#
# This Cmake file creates targets for better warnings
#
# Link to the following targets:
# warning::all  - displays all warnings
# warning::error - treats warnings as errors
#

add_library(warnings_all_ INTERFACE)
add_library(warning::all ALIAS warnings_all_)
target_compile_options(warnings_all_ INTERFACE -Wall -Wextra -Wpedantic)

set(WARNING_INSTALL_TARGET warnings_all_)

add_library(warnings_error_ INTERFACE)
add_library(warning::error ALIAS warnings_error_)
target_compile_options(warnings_error_ INTERFACE -Werror)

set(WARNING_INSTALL_TARGET ${WARNING_INSTALL_TARGET} warnings_error_)
