cmake_minimum_required(VERSION 3.16)

project(game)

set(CMAKE_C_STANDARD 11)

set(SOURCES
    src/game.c
)



# Determine the appropriate flags based on the platform
if(WIN32)
    # On Windows, use WIN32 flag to specify a GUI application (suppresses console)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
elseif(APPLE)
    # On macOS, use MACOSX_BUNDLE to create an App Bundle (suppresses terminal)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES})
else()
    # On other platforms (e.g., Linux), no special flags are needed
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()

target_include_directories(${PROJECT_NAME}
PUBLIC
    include
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    engine
)
