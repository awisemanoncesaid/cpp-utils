# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Minimum C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the library
add_library(Color INTERFACE)

# Specify include directories for the library
target_include_directories(Color INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/CppUtils/Color>
)

# --- Installation ---

install(TARGETS Color
    EXPORT CppUtilsTargets
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/CppUtils/Color
    FILES_MATCHING PATTERN "*.hpp"
)
