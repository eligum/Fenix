#pragma once

#include <memory>
#include <cstddef>

#include "Platform/PlatformDetection.hh"

// TODO: Find a better way to integrate this with the build system
#define FX_DEBUG

#ifdef FX_DEBUG
    #if defined(FX_PLATFORM_WINDOWS)
        #define FX_DEBUGBREAK() __debugbreak()
    #elif defined(FX_PLATFORM_LINUX)
        #include <signal.h>
        #define FX_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #define FX_ENABLE_ASSERTS
#else
    #define FX_DEBUGBREAK()
#endif

#ifndef FX_ENABLE_ASSERTS
    #define FX_ASSERT(x, ...)
    #define FX_CORE_ASSERT(x, ...)
#else
#define FX_ASSERT(x, ...)                                                        \
    {                                                                            \
        if (!(x))                                                                \
        {                                                                        \
            FX_ERROR("Assertion failed at LINE {0} in {1}", __LINE__, __FILE__); \
            FX_ERROR("{0}", __VA_ARGS__);                                        \
        }                                                                        \
    }

#define FX_CORE_ASSERT(x, ...)                                                        \
    {                                                                                 \
        if (!(x))                                                                     \
        {                                                                             \
            FX_CORE_ERROR("Assertion failed at LINE {0} in {1}", __LINE__, __FILE__); \
            FX_CORE_ERROR("{0}", __VA_ARGS__);                                        \
        }                                                                             \
    }
#endif

#define BIT(x) (1 << x)

// #define FX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define FX_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Fenix {

    template <typename T>
    using Scope = std::unique_ptr<T>;

    // template <typename T>
    // using CreateScope = std::make_unique<T>;

    template <typename T>
    using Ref = std::shared_ptr<T>;

    // template <typename T>
    // using CreateRef = std::make_shared<T>;

}

#include "Fenix/Core/Log.hh"
