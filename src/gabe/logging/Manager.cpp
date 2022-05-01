#include <gabe/logging/Manager.hpp>

gabe::logging::Manager::Manager() {}

gabe::logging::Manager::~Manager() {
    for (auto logger : _loggers) {
        delete logger.second;
    }

    printf("All loggers deleted.\n");
}

void gabe::logging::Manager::log(const std::string &logger_name, const SeverityLevel &severity_level, const std::string &log_message) {
}

// gabe::logging::LoggerHandler gabe::logging::Manager::get_logger(const std::string &logger_name) {
//     if (_loggers.find(logger_name) == _loggers.end()) {
//         //setup_logger(logger_name, SeverityLevel::INFO);
//     }
// }
