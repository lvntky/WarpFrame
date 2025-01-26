#ifndef WARPFRAME_LOGGER_H_
#define WARPFRAME_LOGGER_H_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

class Logger {
	public:
		static void init();
		static std::shared_ptr<spdlog::logger> getLogger();
};

#endif // WARPFRAME_LOGGER_H_
