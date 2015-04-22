cmake_minimum_required(VERSION 2.8)
project(opencv_tracking)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCE_FILES main.cpp)
add_executable(opencv_tracking ${SOURCE_FILES} Trackable_Object.cpp Trackable_Object.h Scale.h Scale.h Scale.cpp XML_Writer.cpp XML_Writer.h)
target_link_libraries(opencv_tracking ${OpenCV_LIBS})