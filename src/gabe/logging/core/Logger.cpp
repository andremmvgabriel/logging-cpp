#include <gabe/logging/core/Logger.hpp>

#include <fmt/format.h>

/*
Internal Formatters
*/

gabe::logging::core::Logger::Severity::Severity() : Formatter("SeverityFormatter", "%sev") {}

void gabe::logging::core::Logger::Severity::set_severity(const SeverityLevel &severity) { _severity = severity; }

std::string gabe::logging::core::Logger::Severity::_format() {
    return fmt::format("{:^7}", _formatting[_severity]);
}



gabe::logging::core::Logger::Message::Message() : Formatter("MessageFormatter", "%msg") {}

void gabe::logging::core::Logger::Message::set_message(const std::string &message) { _message = message; }

std::string gabe::logging::core::Logger::Message::_format() {
    return _message;
}

void gabe::logging::core::Logger::Message::format(std::string &message) {
    std::string message_copy = message;

    Formatter::format(message);

    if (message == message_copy) {
        message = message + " " + _message;
    }
}



/*
Logger
*/

gabe::logging::core::Logger::Logger() : _severity(SeverityLevel::INFO) {
    _open_log_file();
    _setup_internal_formatters();
}

gabe::logging::core::Logger::Logger(const gabe::logging::SeverityLevel &severity) : _severity(severity) {
    _open_log_file();
    _setup_internal_formatters();
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

void gabe::logging::core::Logger::_setup_internal_formatters() {
    add_formatter(Severity());
    add_formatter(Message());
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

void gabe::logging::core::Logger::log(const gabe::logging::SeverityLevel &severity, const std::string &message) {
    if ( (uint8_t)severity < (uint8_t)_severity ) return;

    std::string final_log_message = _log_layout;

    // Formatters
    dynamic_cast<Severity*>(_formatters["SeverityFormatter"])->set_severity(severity);

    dynamic_cast<Message*>(_formatters["MessageFormatter"])->set_message(message);

    for (auto formatter : _formatters) {
        formatter.second->format(final_log_message);
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
    if (_sink.should_flush(message)) {
        _sink.flush(_log_file);
    }
    
    _sink.sink_in(final_log_message + "\n");
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

void gabe::logging::core::Logger::set_log_layout(const std::string &log_layout) {
    _log_layout = log_layout;
}
