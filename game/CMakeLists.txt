cmake_minimum_required(VERSION 3.16)

project(game)

set(CMAKE_C_STANDARD 11)

set(SOURCES include/game.h src/game.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC engine)
