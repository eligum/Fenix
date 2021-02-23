#pragma once

#include "Firefly/flypch.hh"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace flyCore {

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

}

// Core log macros
#define FLY_CORE_TRACE(...)   ::flyCore::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FLY_CORE_INFO(...)    ::flyCore::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FLY_CORE_WARN(...)    ::flyCore::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FLY_CORE_ERROR(...)   ::flyCore::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FLY_CORE_FATAL(...)   ::flyCore::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Clien log macros
#define FLY_TRACE(...)        ::flyCore::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FLY_INFO(...)         ::flyCore::Log::GetClientLogger()->info(__VA_ARGS__)
#define FLY_WARN(...)         ::flyCore::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FLY_ERROR(...)        ::flyCore::Log::GetClientLogger()->error(__VA_ARGS__)
#define FLY_FATAL(...)        ::flyCore::Log::GetClientLogger()->critical(__VA_ARGS__)
