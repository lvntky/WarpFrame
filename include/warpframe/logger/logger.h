#ifndef WARPFRAME_LOGGER_H_
#define WARPFRAME_LOGGER_H_

#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

class Logger {
public:
  static void init();
  static std::shared_ptr<spdlog::logger> getLogger();

private:
  static std::shared_ptr<spdlog::logger> logger;
};

#endif // WARPFRAME_LOGGER_H_
