cmake_minimum_required(VERSION 3.1)
project(opencv_tracking)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(opencv_tracking ${SOURCE_FILES} Zippo.cpp Zippo.h)
target_link_libraries(opencv_tracking ${OpenCV_LIBS})