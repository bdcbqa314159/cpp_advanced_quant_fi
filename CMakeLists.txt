cmake_minimum_required(VERSION 3.30)

project(wab_advanced_quant_fi LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configure rpath for proper library linking in install directory
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Set rpath for installed binaries to find libraries
# Binaries in bin/ need to find libraries in ../lib/
if(APPLE)
    set(CMAKE_INSTALL_RPATH "@loader_path;@loader_path/../lib")
elseif(UNIX)
    set(CMAKE_INSTALL_RPATH "$ORIGIN:$ORIGIN/../lib")
endif()

find_package(Python3 COMPONENTS Interpreter Development)

find_package(pybind11 REQUIRED)

MESSAGE(STATUS "the source directory is: ${CMAKE_SOURCE_DIR}")
MESSAGE(STATUS "the binary directory is: ${CMAKE_BINARY_DIR}")

# Set default install location (can be overridden with -DCMAKE_INSTALL_PREFIX=<path>)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "Installation directory" FORCE)
endif()
MESSAGE(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(libraries)
add_subdirectory(apps)