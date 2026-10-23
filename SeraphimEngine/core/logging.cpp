
#include "logging.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace SeraphimEngine
{

    std::shared_ptr<spdlog::logger> Logging::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Logging::s_ClientLogger;

    void Logging::Init() {
        // Pattern format: [Timestamp] [Logger Name] [Log Level]: Message Text
        // %T = ISO 8601 time (HH:MM:SS), %n = Logger name, %^...%$ = Colour codes matching severity
        spdlog::set_pattern("%^[%T] %n: %v%$");

        // Create standard output console loggers with colour support
        s_CoreLogger = spdlog::stdout_color_mt("SeraphimEngine");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
	
}