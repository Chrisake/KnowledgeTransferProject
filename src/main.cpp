#include <iostream>

#include "utils.h"
#include "logger.h"


int main() {
	logging::Logger& logger = logging::Logger::instance();
	logger.add("Console Logger", std::unique_ptr<logging::LogHandler>(new logging::ConsoleHandler({ "console",logging::log_level::debug })));
	
	
	logger.fatal(std::to_string(utils::reverse(1234)));
	logger.error(std::to_string(utils::reverse(235617)));
	logger.warn(std::to_string(utils::reverse(5849648)));
	logger.info(std::to_string(utils::reverse(19838419)));
	logger.debug(utils::reverse("Hello World"));
	logger.debug(utils::reverse("abcdEFGhijkLMNOP"));
	return 0;
}