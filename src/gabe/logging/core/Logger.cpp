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
    _delete_formatters();
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

void gabe::logging::core::Logger::_delete_formatters() {
    for (auto formatter : _formatters) {
        delete formatter.second;
    }
}

void gabe::logging::core::Logger::log(const gabe::logging::SeverityLevel &severity, std::string message) {
    if ( (uint8_t)severity < (uint8_t)_severity ) return;

    // Formatters
    for (const std::string &formatter_type : _formatters_order) {
        _formatters[formatter_type]->format(message);
    }

    // Handlers
    // for (auto handler : _handlers) {
    //     if (handler.second->evaluate()) {
    //         _sink.flush(_log_file);
    //         _close_log_file();
    //         handler.second->handle();
    //         _open_log_file();
    //     }
    // }

    // Sink management
    if (_sink.should_flush(message))
        _sink.flush(_log_file);
    
    _sink.sink_in(message + "\n");
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
