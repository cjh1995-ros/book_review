cmake_minimum_required(VERSION 3.10)
project(cpp_threading)

set(CMAKE_CXX_STANDARD 17)


# Specify project files and locations
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")


include_directories("${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include")

set(EXAMPLE_DIR	"${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/src")
file(GLOB EXAMPLE_FILES ${EXAMPLE_DIR}/*.cpp)


add_executable(example_scheduler 
    ${EXAMPLE_DIR}/example_scheduler.cpp
    ${EXAMPLE_DIR}/request.cpp
    ${EXAMPLE_DIR}/dispatcher.cpp
    ${EXAMPLE_DIR}/worker.cpp)

