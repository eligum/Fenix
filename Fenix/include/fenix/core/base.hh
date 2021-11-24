#pragma once

#include <memory>
#include <cstddef>
#include <cassert>

#include "platform/platform_detection.hh"

// TODO: Find a better way to integrate this with the build system
#define FENIX_DEBUG

#ifdef FENIX_DEBUG
    #if defined(FENIX_PLATFORM_WINDOWS)
        #define FENIX_DEBUGBREAK() __debugbreak()
    #elif defined(FENIX_PLATFORM_LINUX)
        #include <signal.h>
        #define FENIX_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #define FENIX_ENABLE_ASSERTS
#else
    #define FENIX_DEBUGBREAK()
#endif

#ifndef FENIX_ENABLE_ASSERTS
    #define FENIX_ASSERT(condition, ...) assert(condition)
    #define FENIX_CORE_ASSERT(x, ...)
#else
#define FENIX_ASSERT(x, ...)                                                        \
    {                                                                               \
        if (!(x))                                                                   \
        {                                                                           \
            FENIX_ERROR("Assertion failed at LINE {0} in {1}", __LINE__, __FILE__); \
            FENIX_ERROR("{0}", __VA_ARGS__);                                        \
        }                                                                           \
    }

#define FENIX_CORE_ASSERT(x, ...)                                                        \
    {                                                                                    \
        if (!(x))                                                                        \
        {                                                                                \
            FENIX_CORE_ERROR("Assertion failed at LINE {0} in {1}", __LINE__, __FILE__); \
            FENIX_CORE_ERROR("{0}", __VA_ARGS__);                                        \
        }                                                                                \
    }
#endif

#define BIT(x) (1 << x)

// #define FENIX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define FENIX_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace fenix {

    template <typename T>
    using Scope = std::unique_ptr<T>;
    template <typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;
    template <typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}

#include "fenix/core/log.hh"
