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

void gabe::logging::LoggerHandler::trace(const std::string &message) {
    _logger->trace(message);
}

void gabe::logging::LoggerHandler::debug(const std::string &message) {
    _logger->debug(message);
}

void gabe::logging::LoggerHandler::info(const std::string &message) {
    _logger->info(message);
}

void gabe::logging::LoggerHandler::warning(const std::string &message) {
    _logger->warning(message);
}

void gabe::logging::LoggerHandler::error(const std::string &message) {
    _logger->error(message);
}

void gabe::logging::LoggerHandler::fatal(const std::string &message) {
    _logger->fatal(message);
}
