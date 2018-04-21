cmake_minimum_required(VERSION 2.8)
set (PROJECT_NAME "count_dice_dots")
project(${PROJECT_NAME})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable (${PROJECT_NAME} count_dice_dots.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
