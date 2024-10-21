@echo off
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

:: Get the directory where the script is located
SET "SCRIPT_DIR=%~dp0"

if "%~1"=="" (
    echo Usage: %~nx0 [debug^|release]
    exit /b 1
)

set BUILD_TYPE=%~1

if /I "%BUILD_TYPE%"=="debug" (
    set CMAKE_BUILD_TYPE=Debug
) else if /I "%BUILD_TYPE%"=="release" (
    set CMAKE_BUILD_TYPE=Release
) else (
    echo Invalid build type: %BUILD_TYPE%
    echo Usage: %~nx0 [debug^|release]
    exit /b 1
)

:: Check if cmake is installed
where cmake >nul 2>&1
if errorlevel 1 (
    echo cmake could not be found. Please install cmake.
    exit /b 1
)

set BUILD_DIR=%SCRIPT_DIR%build\%BUILD_TYPE%

if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

cmake -S "%SCRIPT_DIR%" -B "%BUILD_DIR%" -DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE%
cmake --build "%BUILD_DIR%"
ENDLOCAL
