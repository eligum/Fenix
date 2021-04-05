#pragma once

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Fenix {

    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

} // namespace Fenix

// Core log macros
#define FX_CORE_TRACE(...)   ::Fenix::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FX_CORE_INFO(...)    ::Fenix::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FX_CORE_WARN(...)    ::Fenix::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FX_CORE_ERROR(...)   ::Fenix::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FX_CORE_FATAL(...)   ::Fenix::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Clien log macros
#define FX_TRACE(...)        ::Fenix::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FX_INFO(...)         ::Fenix::Log::GetClientLogger()->info(__VA_ARGS__)
#define FX_WARN(...)         ::Fenix::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FX_ERROR(...)        ::Fenix::Log::GetClientLogger()->error(__VA_ARGS__)
#define FX_FATAL(...)        ::Fenix::Log::GetClientLogger()->critical(__VA_ARGS__)
