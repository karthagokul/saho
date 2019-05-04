project(saho-common)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_library(${PROJECT_NAME} ${SRC_LIST})
add_library(saho::common ALIAS ${PROJECT_NAME})

