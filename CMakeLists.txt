cmake_minimum_required(VERSION 3.5.1)
project(my_du)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

add_executable(test_find_matches src/test_find_matches.cpp src/find_matches.cpp)
target_link_libraries(test_find_matches ${OpenCV_LIBS})