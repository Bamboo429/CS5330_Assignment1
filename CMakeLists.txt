cmake_minimum_required(VERSION 3.21)
project(Real_time_filtering)

find_package(OpenCV)
include_directories(${/usr/local/include/})

set(CMAKE_CXX_STANDARD 17)

add_executable(Real_time_filtering vidDisplay.cpp imgDisplay.cpp imgDisplay.h vidDisplay.cpp vidDisplay.h filter.cpp filter.h)
target_link_libraries(Real_time_filtering ${OpenCV_LIBS})