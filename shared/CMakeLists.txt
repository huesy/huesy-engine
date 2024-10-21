cmake_minimum_required(VERSION 3.16)

project(shared)

set(CMAKE_C_STANDARD 11)

set(SOURCES include/defines.h src/shared.c)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
