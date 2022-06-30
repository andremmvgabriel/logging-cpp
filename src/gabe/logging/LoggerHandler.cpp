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

gabe::logging::core::Logger* gabe::logging::LoggerHandler::ptr() {
    return _logger;
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

void gabe::logging::LoggerHandler::set_log_layout(const std::string &log_layout) {
    _logger->set_log_layout(log_layout);
}

std::string gabe::logging::LoggerHandler::get_log_layout() {
    return _logger->get_log_layout();
}

void gabe::logging::LoggerHandler::set_chained_logs(bool active) {
    _logger->set_chained_logs(active);
}

bool gabe::logging::LoggerHandler::get_chained_logs() {
    return _logger->get_chained_logs();
}

void gabe::logging::LoggerHandler::set_severity(const SeverityLevel &severity) {
    _logger->set_severity(severity);
}

gabe::logging::SeverityLevel gabe::logging::LoggerHandler::get_severity() {
    return _logger->get_severity();
}

void gabe::logging::LoggerHandler::set_logs_location(const std::string &location) {
    _logger->set_logs_location(location);
}

std::string gabe::logging::LoggerHandler::get_logs_location() {
    return _logger->get_logs_location();
}

void gabe::logging::LoggerHandler::set_logs_file_name(const std::string &file_name) {
    _logger->set_logs_file_name(file_name);
}

std::string gabe::logging::LoggerHandler::get_logs_file_name() {
    return _logger->get_logs_file_name();
}

void gabe::logging::LoggerHandler::basic_config(const SeverityLevel &severity, const std::string &location, const std::string &file_name) {
    _logger->basic_config(severity, location, file_name);
}
