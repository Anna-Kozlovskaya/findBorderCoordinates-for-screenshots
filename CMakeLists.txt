cmake_minimum_required(VERSION 3.19)
project(findBorderCoordinates)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( OpenCV REQUIRED )
set(SOURCE_FILES main.cpp)
add_executable(findBorderCoordinates main.cpp)

include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( findBorderCoordinates ${OpenCV_LIBS} )
