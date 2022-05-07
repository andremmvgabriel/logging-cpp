#include <gabe/logging/Manager.hpp>

gabe::logging::Manager::Manager() {}

gabe::logging::Manager::~Manager() {
    for (auto logger : _loggers) {
        delete logger.second;
    }

    printf("All loggers deleted.\n");
}

void gabe::logging::Manager::log(const std::string &logger_name, const SeverityLevel &severity, const std::string &message) {
    LoggerHandler logger = get_logger(logger_name);
    logger.log(severity, message);
}

gabe::logging::LoggerHandler gabe::logging::Manager::get_logger(const std::string &logger_name) {
    if (_loggers.find(logger_name) == _loggers.end()) {
        setup_logger(logger_name);
    }

    return LoggerHandler(_loggers[logger_name]);
}

void gabe::logging::Manager::setup_logger(const std::string &logger_name) {
    if (_loggers.find(logger_name) != _loggers.end()) return;

    _loggers[logger_name] = new core::Logger();
}
