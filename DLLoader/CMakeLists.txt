# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Minimum C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the library
add_library(DLLoader INTERFACE)

# Specify include directories for the library
target_include_directories(DLLoader INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/CppUtils/DLLoader>
)

if (UNIX)
    target_link_libraries(DLLoader INTERFACE -ldl)
endif()

# --- Installation ---

install(TARGETS DLLoader
    EXPORT CppUtilsTargets
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/CppUtils/DLLoader
    FILES_MATCHING PATTERN "*.hpp"
)
