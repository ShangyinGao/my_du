cmake_minimum_required(VERSION 3.5.1)
project(my_du)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_subdirectory(src/common)

set(MY_DU_MODULES my_du_common)

file(WRITE ${PROJECT_BINARY_DIR}/empty.cpp)
add_library(my_du SHARED ${PROJECT_BINARY_DIR}/empty.cpp)

target_link_libraries(my_du ${MY_DU_MODULES})
target_compile_options(my_du PRIVATE -O3)
target_compile_options(my_du PRIVATE -Wall)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(STATUS "compile test for my_du")
    add_subdirectory(test)
endif()
