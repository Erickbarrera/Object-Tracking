cmake_minimum_required(VERSION 2.8.4)
project(openni-tracking)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(PCL 1.8)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

 set(PCL_BUILD_TYPE Release)

 file(GLOB ${SOURCE_FILES}
     "src/*.h"
     "src/*.cpp"
 )

set(SOURCE_FILES main.cpp)
add_executable(openni-tracking ${SOURCE_FILES})
target_link_libraries (openni-tracking ${PCL_LIBRARIES})
