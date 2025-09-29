# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Minimum C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the library
add_library(DLLoader INTERFACE)

# Specify include directories for the library
target_include_directories(DLLoader INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if (UNIX)
    target_link_libraries(DLLoader INTERFACE -ldl)
endif()
