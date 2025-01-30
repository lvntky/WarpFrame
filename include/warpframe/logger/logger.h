#ifndef WARPFRAME_LOGGER_H_
#define WARPFRAME_LOGGER_H_

#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

class Logger {
public:
  static void init();
  static std::shared_ptr<spdlog::logger> getLogger();
};

#endif // WARPFRAME_LOGGER_H_
