cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Library ---

add_library(Signal INTERFACE)

target_include_directories(Signal INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/CppUtils/Signal>
)

# --- Installation ---

install(TARGETS Signal
    EXPORT CppUtilsTargets
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/CppUtils/Signal
    FILES_MATCHING PATTERN "*.hpp"
)
