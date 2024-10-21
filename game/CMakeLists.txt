cmake_minimum_required(VERSION 3.16)

project(game)

set(CMAKE_C_STANDARD 11)

set(SOURCES
    src/game.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
PUBLIC
    include
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    engine
)

# # Post-build step to copy SDL DLLs (if using dynamic linking on Windows)
# if (WIN32)
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different
#             $<TARGET_FILE:SDL3::SDL3>
#             $<TARGET_FILE_DIR:${PROJECT_NAME}>
#     )
# endif()
