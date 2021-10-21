#include "core/log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace momo {

std::shared_ptr<spdlog::logger> Log::logger;
std::shared_ptr<spdlog::logger> Log::core_logger;
std::shared_ptr<spdlog::logger> Log::error_logger;

void Log::init()
{
    logger = spdlog::stdout_color_mt("HOST");
    logger->set_pattern("%^%v%$");
    logger->set_level(spdlog::level::trace);

    core_logger = spdlog::stdout_color_mt("CORE");
    core_logger->set_pattern("%^%v%$");
    core_logger->set_level(spdlog::level::trace);

    error_logger = spdlog::stderr_color_mt("ERROR");
    error_logger->set_pattern("%^%v%$");
    error_logger->set_level(spdlog::level::err);
}

} // namespace momo