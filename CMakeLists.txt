cmake_minimum_required(VERSION 3.0)



set(NAME "ra")

project(${NAME})

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../)




file(GLOB ${NAME}_HEADERS *.hpp)

file(GLOB ${NAME}_SOURCES *.cpp)


add_executable(${NAME} ${${NAME}_HEADERS} ${${NAME}_SOURCES})

