#include "fenix/core/log.hh"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace fenix {

    std::shared_ptr<spdlog::logger> Log::s_core_logger;
    std::shared_ptr<spdlog::logger> Log::s_client_logger;

    void Log::Init()
    {
        std::vector<spdlog::sink_ptr> log_sinks;
        log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        log_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("fenix.log", true));

        log_sinks[0]->set_pattern("[%T]%^ %n: %v%$");
        log_sinks[1]->set_pattern("[%T] [%l] %n: %v");

        s_core_logger = std::make_shared<spdlog::logger>("FENIX", begin(log_sinks), end(log_sinks));
        spdlog::register_logger(s_core_logger);
        s_core_logger->set_level(spdlog::level::trace);
        s_core_logger->flush_on(spdlog::level::trace);

        s_client_logger = std::make_shared<spdlog::logger>("APP", begin(log_sinks), end(log_sinks));
        spdlog::register_logger(s_client_logger);
        s_client_logger->set_level(spdlog::level::trace);
        s_client_logger->flush_on(spdlog::level::trace);
    }

} // namespace fenix
