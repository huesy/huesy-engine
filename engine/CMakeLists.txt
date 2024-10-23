cmake_minimum_required(VERSION 3.16)

project(engine)

set(CMAKE_C_STANDARD 11)

# Define sources
# set(SOURCES
#     src/engine.c
# )
file(GLOB SOURCES
    "src/*.c"
    "src/platform/*.c"
    "src/renderer/*.c"
)

# Create library
# - STATIC: static library (.a, .lib)
# - SHARED: shared library (.so, .dll, .dylib)
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME}
PUBLIC
    include
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
PUBLIC
    shared
    SDL3::SDL3
)

# Define ENGINE_EXPORT only for the engine library.
target_compile_definitions(${PROJECT_NAME} PRIVATE ENGINE_EXPORT)
