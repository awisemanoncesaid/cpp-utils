cmake_minimum_required(VERSION 3.10)
project(CppUtils VERSION 1.0.0 LANGUAGES CXX)

# --- Library ---

add_subdirectory(Math)
add_subdirectory(Color)
add_subdirectory(DLLoader)
add_subdirectory(Signal)

add_library(CppUtils INTERFACE)
target_link_libraries(CppUtils INTERFACE
    CppUtils::Math
    CppUtils::Color
    CppUtils::DLLoader
    CppUtils::Signal
)

# --- Install ---

# Export all targets for installation
install(EXPORT CppUtilsTargets
    FILE CppUtilsTargets.cmake
    NAMESPACE CppUtils::
    DESTINATION lib/cmake/CppUtils
)

# Generate Config files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/CppUtilsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CppUtilsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/CppUtilsConfig.cmake"
    INSTALL_DESTINATION lib/cmake/CppUtils
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/CppUtilsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/CppUtilsConfigVersion.cmake"
    DESTINATION lib/cmake/CppUtils
)
