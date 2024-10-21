cmake_minimum_required(VERSION 3.5)

project(shared)

set(CMAKE_C_STANDARD 11)

set(SOURCES
    src/shared.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)
