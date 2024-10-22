@echo off
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

:: Get the directory where the script is located
SET "SCRIPT_DIR=%~dp0"
:: Remove the trailing backslash if present
SET "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

if "%~1"=="" (
    echo Usage: %~nx0 [debug^|release]
    exit /b 1
)

set "BUILD_TYPE=%~1"

if /I "%BUILD_TYPE%"=="debug" (
    set "CMAKE_BUILD_TYPE=Debug"
) else if /I "%BUILD_TYPE%"=="release" (
    set "CMAKE_BUILD_TYPE=Release"
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

set "BUILD_DIR=%SCRIPT_DIR%\build\%BUILD_TYPE%"

if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

:: Run cmake with MinGW Makefiles generator
cmake -G "MinGW Makefiles" -S "%SCRIPT_DIR%" -B "%BUILD_DIR%" -DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE%

:: Build using cmake
cmake --build "%BUILD_DIR%"
ENDLOCAL
