cmake_minimum_required(VERSION 3.16)

project(Huesy)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set output directories for all targets
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Vendor subdirectories
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)

# Other subdirectories
add_subdirectory(shared)
add_subdirectory(engine)
add_subdirectory(game)
