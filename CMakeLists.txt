cmake_minimum_required(VERSION 3.5.1)
project(my_du)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

add_executable(test_find_matches src/test_find_matches.cpp src/find_matches.cpp src/utility.cpp src/utility.h)
target_link_libraries(test_find_matches ${OpenCV_LIBS})

add_executable(test_read_kitti src/test_read_kitti.cpp src/read_kitti.cpp src/utility.cpp src/utility.h)
target_link_libraries(test_read_kitti ${OpenCV_LIBS})

add_executable(test_demo src/test_demo.cpp)
