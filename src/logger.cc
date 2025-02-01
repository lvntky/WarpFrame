#include <iostream>
#include <vector>
#include <warpframe/logger/logger.h>

std::shared_ptr<spdlog::logger> Logger::logger;
static bool isInit = false;

void Logger::init() {
  try {
    // Create vector of sinks
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        "warpframe.log", true);

    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

    logger = std::make_shared<spdlog::logger>("WarpFrameLogger", sinks.begin(),
                                              sinks.end());

    logger->set_pattern("[%d-%m-%Y %H:%M:%S] [%^%l%$] %v");

    logger->set_level(spdlog::level::info);

    spdlog::set_default_logger(logger);

    logger->info("Logger initialized with console and file output.");
    isInit = true;
  } catch (const spdlog::spdlog_ex& ex) {
    std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
  }
}

std::shared_ptr<spdlog::logger> Logger::getLogger() {
  return logger;
}
