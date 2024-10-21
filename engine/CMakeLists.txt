cmake_minimum_required(VERSION 3.16)

project(engine)

set(CMAKE_C_STANDARD 11)

set(SOURCES include/defines.h src/engine.c)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
# Alternatively, use STATIC if you do not need a shared library.

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC shared)
