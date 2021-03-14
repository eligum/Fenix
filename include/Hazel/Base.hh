#pragma once

#include <memory>
#include <cstddef>

#include "PlatformDetection.hh"

#ifdef HZ_DEBUG
    #if defined(HZ_PLATFORM_WINDOWS)
        #define HZ_DEBUGBREAK() __debugbreak()
    #elif defined(HZ_PLATFORM_LINUX)
        #include <signal.h>
        #define HZ_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #define HZ_ENABLE_ASSERTS
#else
    #define HZ_DEBUGBREAK()
#endif

#ifdef HZ_ENABLE_ASSERTS
    #define HZ_ASSERT(x, ...)
    #define HZ_CORE_ASSERT(x, ...)
#else
    #define HZ_ASSERT(x, ...) { if (!(x)) { HZ_ERROR("Assertion failed at LINE {0} in {1}", __LINE__, __FILE__); \
                                            HZ_ERROR("{0}", __VA_ARGS__); } }
    #define HZ_CORE_ASSERT(x, ...) { if (!(x)) { HZ_CORE_ERROR("Assertion failed at LINE {0} in {1}", __LINE__, __FILE__); \
                                                 HZ_CORE_ERROR("{0}", __VA_ARGS__); } }
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
// #define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {

    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T>
    using Ref = std::shared_ptr<T>;

}

#include "Core/Log.hh"
