#pragma once

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace fenix {

    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_core_logger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_client_logger; }
    private:
        static std::shared_ptr<spdlog::logger> s_core_logger;
        static std::shared_ptr<spdlog::logger> s_client_logger;
    };

} // namespace fenix

// Core log macros
#define FENIX_CORE_TRACE(...)   ::fenix::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FENIX_CORE_INFO(...)    ::fenix::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FENIX_CORE_WARN(...)    ::fenix::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FENIX_CORE_ERROR(...)   ::fenix::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FENIX_CORE_FATAL(...)   ::fenix::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Clien log macros
#define FENIX_TRACE(...)        ::fenix::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FENIX_INFO(...)         ::fenix::Log::GetClientLogger()->info(__VA_ARGS__)
#define FENIX_WARN(...)         ::fenix::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FENIX_ERROR(...)        ::fenix::Log::GetClientLogger()->error(__VA_ARGS__)
#define FENIX_FATAL(...)        ::fenix::Log::GetClientLogger()->critical(__VA_ARGS__)
