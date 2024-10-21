#!/bin/bash

set -e

# Get the directory where the script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 [debug|release]"
    exit 1
fi

BUILD_TYPE=$1

if [[ "$BUILD_TYPE" != "debug" && "$BUILD_TYPE" != "release" ]]; then
    echo "Invalid build type: $BUILD_TYPE"
    echo "Usage: $0 [debug|release]"
    exit 1
fi

# Check if cmake is installed
if ! command -v cmake &> /dev/null
then
    echo "cmake could not be found. Please install cmake."
    exit 1
fi

BUILD_DIR="${SCRIPT_DIR}/build/${BUILD_TYPE}"

if [ "$BUILD_TYPE" == "debug" ]; then
    CMAKE_BUILD_TYPE=Debug
elif [ "$BUILD_TYPE" == "release" ]; then
    CMAKE_BUILD_TYPE=Release
fi

mkdir -p "${BUILD_DIR}"
cmake -S "${SCRIPT_DIR}" -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
cmake --build "${BUILD_DIR}"
