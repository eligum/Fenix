#pragma once

#include <memory>
#include <utility>

#include "Log.hh"
#include "PlatformDetection.hh"

#ifdef FLY_DEBUG
    #if defined(FLY_PLATFORM_WINDOWS)
        #define FLY_DEBUGBREAK() __debugbreak()
    #elif defined(FLY_PLATFORM_LINUX)
        #include <signal.h>
        #define FLY_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #define FLY_ENABLE_ASSERTS
#else
    #define FLY_DEBUGBREAK()
#endif

#ifdef FLY_ENABLE_ASSERTS
    #define FLY_ASSERT(x, ...)
    #define FLY_CORE_ASSERT(x, ...)
#else
    #define FLY_ASSERT(x, ...) { if (!(x)) { FLY_ERROR("Assertion failed: {0}", __VA_ARGS__); } }
    #define FLY_CORE_ASSERT(x, ...) { if (!(x)) { FLY_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); } }
#endif

#define BIT(x) (1 << x)

#define FLY_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
