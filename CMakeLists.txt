#########################
# @file: CMakeLists.txt #
# @author: Gresces      #
# @date: 2024-6-30      #
#########################

cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)

project(Adaxia)
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

# Compile config
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_options(-Werror -g)
    message(STATUS "Compile type: ${CMAKE_BUILD_TYPE}")
else(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_BUILD_TYPE Release)
    add_compile_options(-Werror -Os)
    message(STATUS "Compile type: ${CMAKE_BUILD_TYPE}")
endif(CMAKE_BUILD_TYPE MATCHES Debug)

# File structure
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)   # Bin Path : bin
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)      # Lib Path : lib
set(RESC_DIR ${PROJECT_SOURCE_DIR}/resource)
set(MODULE_DIR ${PROJECT_SOURCE_DIR}/module)

# Packages
find_package(oatpp REQUIRED)

# Compile and build
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
## Static libs
add_subdirectory(${MODULE_DIR})

add_executable(${PROJECT_NAME} main.cc ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} 
    AdaxiaLog
    AdaxiaConfig
    oatpp::oatpp
)
