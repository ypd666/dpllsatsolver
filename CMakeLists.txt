cmake_minimum_required(VERSION 3.21)
project(dpllsatsolver)
add_executable(dpllsatsolver src/main.cpp src/algo.cpp src/getin.cpp)
set_target_properties(dpllsatsolver PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")