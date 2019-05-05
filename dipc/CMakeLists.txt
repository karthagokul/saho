project(saho-dipc)
cmake_minimum_required(VERSION 2.8)
INCLUDE_DIRECTORIES(../common)


aux_source_directory(. SRC_LIST)
add_library(${PROJECT_NAME} ${SRC_LIST})
add_library(saho::dipc ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} saho::common pthread)
