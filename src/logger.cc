#include <warpframe/logger/logger.h>

std::shared_ptr<spdlog::logger> logger;

void Logger::init() {
    logger = spdlog::basic_logger_mt("WarpFrameLogger", "warpframe.log", true);
    spdlog::set_pattern("[%d-%m-%Y %H:%M:%S] [%^%L%$] %v");
    logger->set_level(spdlog::level::info);

    spdlog::set_default_logger(logger);

    spdlog::info("Logger initialized.");
}

std::shared_ptr<spdlog::logger> Logger::getLogger() { return logger; }
