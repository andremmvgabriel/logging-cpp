#include <gabe/logging/LoggerHandler.hpp>

gabe::logging::LoggerHandler::LoggerHandler() {}

gabe::logging::LoggerHandler::LoggerHandler(gabe::logging::core::Logger *logger) : _logger(logger) {}

gabe::logging::LoggerHandler::LoggerHandler(const gabe::logging::LoggerHandler &logger_handler) {
    _logger = logger_handler._logger;
}

gabe::logging::LoggerHandler& gabe::logging::LoggerHandler::operator=(const gabe::logging::LoggerHandler &logger_handler) {
    _logger = logger_handler._logger;
    return *this;
}

void gabe::logging::LoggerHandler::log(const gabe::logging::SeverityLevel &severity, const std::string &message) {
    _logger->log(severity, message);
}
