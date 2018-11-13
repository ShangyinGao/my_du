project(my_du_test)

include_directories(include)
file(GLOB CPP_FILES src/*.cpp)

foreach(SAMPLE_SOURCE ${CPP_FILES})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" SAMPLE_NAME ${SAMPLE_SOURCE})
    message(STATUS "one test file: " ${SAMPLE_NAME})
    add_executable(${SAMPLE_NAME} ${SAMPLE_SOURCE})
    target_link_libraries(${SAMPLE_NAME} my_du)
endforeach(SAMPLE_SOURCE ${CPP_FILES})
