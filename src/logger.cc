#include "../include/warpframe/logger/logger.h"

std::shared_ptr<spdlog::logger> logger;

void Logger::init() {
	logger = spdlog::basic_logger_mt("WarpFrameLogger", "warpframe.log", true);
	spdlog::set_pattern("[%d-%m-%Y %H:%M:%S] [%^%1%$] %v");
	logger->set_level(spdlog::level::info);
	spdlog::info("Logger initialized.");
}

std::shared_ptr<spdlog::logger> Logger::getLogger() {
	return logger;
}
