#include <gabe/logging/core/Logger.hpp>

gabe::logging::core::Logger::Logger() : _severity(SeverityLevel::INFO) {
    _open_log_file();
}

gabe::logging::core::Logger::Logger(const gabe::logging::SeverityLevel &severity) : _severity(severity) {
    _open_log_file();
}

gabe::logging::core::Logger::~Logger() {
    _sink.flush(_log_file);
    _close_log_file();
    _delete_handlers();
}

void gabe::logging::core::Logger::_open_log_file() {
    if (_log_file.is_open()) return;

    _log_file = std::ofstream(
        "log_file.txt",
        std::ios::out | std::ios::app
    );
}

void gabe::logging::core::Logger::_close_log_file() {
    if (!_log_file.is_open()) return;

    _log_file.close();
}

void gabe::logging::core::Logger::_delete_handlers() {
    for (auto handler : _handlers) {
        delete handler.second;
    }
}

void gabe::logging::core::Logger::log(const gabe::logging::SeverityLevel &severity, const std::string &message) {
    if ( (uint8_t)severity < (uint8_t)_severity ) return;
    
    if (_sink.should_flush(message))
        _sink.flush(_log_file);
    
    _sink.sink_in(message);
}

void gabe::logging::core::Logger::trace(const std::string &message) {
    log(SeverityLevel::TRACE, message);
}

void gabe::logging::core::Logger::debug(const std::string &message) {
    log(SeverityLevel::DEBUG, message);
}

void gabe::logging::core::Logger::info(const std::string &message) {
    log(SeverityLevel::INFO, message);
}

void gabe::logging::core::Logger::warning(const std::string &message) {
    log(SeverityLevel::WARNING, message);
}

void gabe::logging::core::Logger::error(const std::string &message) {
    log(SeverityLevel::ERROR, message);
}

void gabe::logging::core::Logger::fatal(const std::string &message) {
    log(SeverityLevel::FATAL, message);
}
