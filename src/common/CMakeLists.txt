project(my_du_common)

include_directories(include)
file(GLOB_RECURSE CPP_FILES src/*.cpp)

find_package(OpenCV REQUIRED)

add_library(${PROJECT_NAME} ${CPP_FILES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include}})
