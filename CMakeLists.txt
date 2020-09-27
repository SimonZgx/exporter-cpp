cmake_minimum_required(VERSION 2.8)

project(exporter-cpp)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. SRC_DIR)
include_directories(.)

add_executable(${PROJECT_NAME} ${SRC_DIR})
