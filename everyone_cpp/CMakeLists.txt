cmake_minimum_required(VERSION 3.10)
project(everyone_cpp)

set(CMAKE_CXX_STANDARD 17)


# Specify project files and locations
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")


include_directories("${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include")

set(EXAMPLE_DIR	"${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/src")
file(GLOB EXAMPLE_FILES ${EXAMPLE_DIR}/*.cpp)


foreach(example_file ${EXAMPLE_FILES})
    string(REPLACE ".cpp"            "" example_name ${example_file})
    string(REPLACE "${EXAMPLE_DIR}/" "" example_name ${example_name})
    # add_executable(${PROJECT_NAME}/${example_name} ${example_file})
    add_executable(${example_name} ${example_file})
endforeach()