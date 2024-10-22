#include "engine/platform.h"

// We're using SDL3 which should cover most platforms.
#include "platform_sdl3.c"

// If you want to support multiple platforms, you can include platform-specific
// #if defined(PLATFORM_WINDOWS)
// #	include "platform_windows.c"
// #elif defined(PLATFORM_LINUX)
// #	include "platform_macos.c"
// #elif defined(PLATFORM_MACOS)
// #	include "platform_linux.c"
// #else
// #	error "Unknown platform"
// #endif
