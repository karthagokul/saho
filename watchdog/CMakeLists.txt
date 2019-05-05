project(watchdog)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
INCLUDE_DIRECTORIES(../common)
INCLUDE_DIRECTORIES(../dipc)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} saho::common saho::dipc -lpthread)

