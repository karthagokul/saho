project(examples)
cmake_minimum_required(VERSION 2.8)
INCLUDE_DIRECTORIES(../common)
add_executable(${PROJECT_NAME}-common common.cpp)
target_link_libraries(${PROJECT_NAME}-common saho::common)

