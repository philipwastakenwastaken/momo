
#pragma once

#include <memory>

#define FMT_DEPRECATED
#include "core/core.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace momo {

class Log
{
  public:
    Log() = delete;
    ~Log() = delete;

    static void init();
    inline static std::shared_ptr<spdlog::logger>& get_logger() { return logger; }
    inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return core_logger; }
    inline static std::shared_ptr<spdlog::logger>& get_error_logger() { return error_logger; }

  private:
    static std::shared_ptr<spdlog::logger> logger;
    static std::shared_ptr<spdlog::logger> core_logger;
    static std::shared_ptr<spdlog::logger> error_logger;
};

} // namespace momo

#ifdef MOMO_ENABLE_LOGGING
#define MOMO_ERROR(...) ::momo::Log::get_error_logger()->error(__VA_ARGS__)
#define MOMO_WARN(...) ::momo::Log::get_logger()->warn(__VA_ARGS__)
#define MOMO_INFO(...) ::momo::Log::get_logger()->info(__VA_ARGS__)
#define MOMO_TRACE(...) ::momo::Log::get_logger()->trace(__VA_ARGS__)
#define MOMO_CRITICAL(...) ::momo::Log::get_logger()->critical(__VA_ARGS__)
#else
#define MOMO_ERROR(...)
#define MOMO_WARN(...)
#define MOMO_INFO(...)
#define MOMO_TRACE(...)
#define MOMO_CRITICAL(...)
#endif

// These are always present. Use for logging that is actually part of the program
#define MOMO_CORE_ERROR(...) ::momo::Log::get_core_logger()->error(__VA_ARGS__)
#define MOMO_CORE_WARN(...) ::momo::Log::get_core_logger()->warn(__VA_ARGS__)
#define MOMO_CORE_INFO(...) ::momo::Log::get_core_logger()->info(__VA_ARGS__)
#define MOMO_CORE_TRACE(...) ::momo::Log::get_core_logger()->trace(__VA_ARGS__)
#define MOMO_CORE_CRITICAL(...) ::momo::Log::get_core_logger()->critical(__VA_ARGS__)