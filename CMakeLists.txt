cmake_minimum_required(VERSION 3.30)

project(cpp_advanced_quant_fi LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find_package(GSL REQUIRED)
# find_package(Boost REQUIRED COMPONENTS date_time)

add_subdirectory(quant_fi)

add_subdirectory(testing)

