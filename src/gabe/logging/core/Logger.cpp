#include <gabe/logging/core/Logger.hpp>

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

gabe::logging::core::Logger::Logger() : _severity(SeverityLevel::INFO), _parent(nullptr) {
    _sink = new Sink("logs", "log.txt");
    _setup_internal_formatters();
}

gabe::logging::core::Logger::Logger(const std::string &location, const std::string &name, Logger* parent) : _severity(SeverityLevel::INFO), _parent(parent) {
    _sink = new Sink(location, name + ".txt");
    _setup_internal_formatters();
}

gabe::logging::core::Logger::Logger(const std::string &location, const std::string &name, const gabe::logging::SeverityLevel &severity) : _severity(severity), _parent(nullptr) {
    _sink = new Sink(location, name + ".txt");
    _setup_internal_formatters();
}

gabe::logging::core::Logger::Logger(const std::string &location, const std::string &name, const gabe::logging::SeverityLevel &severity, Logger *parent) : _severity(severity), _parent(parent) {
    _sink = new Sink(location, name + ".txt");
    _setup_internal_formatters();
}

gabe::logging::core::Logger::~Logger() {
    _delete_sink();
    _delete_handlers();
    _delete_formatters();
    _parent = nullptr;
}

void gabe::logging::core::Logger::_setup_internal_formatters() {
    add_formatter(Severity());
    add_formatter(Message());
}

void gabe::logging::core::Logger::_delete_sink() {
    _sink->flush();
    delete _sink;
    _sink = nullptr;
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

void gabe::logging::core::Logger::_log(const SeverityLevel &severity, const std::string &message) {
    std::lock_guard<std::mutex> lock_guard(_log_mutex);

    if ( (uint8_t)severity < (uint8_t)_severity ) return;

    std::string final_log_message = _log_layout;

    // Formatters
    dynamic_cast<Severity*>(_formatters["SeverityFormatter"])->set_severity(severity);

    dynamic_cast<Message*>(_formatters["MessageFormatter"])->set_message(message);

    for (auto formatter : _formatters) {
        formatter.second->format(final_log_message);
    }

    final_log_message += "\n";

    // Handlers
    for (auto handler : _handlers) {
        handler.second->handle(_sink, final_log_message);
    }

    // Sink management
    if (_sink->should_flush(message)) {
        _sink->flush();
    }
    
    _sink->sink_in(final_log_message);

    // Also logs into parent if existent, and allowed
    if (_parent && _chained_logs) _parent->log(severity, message);
}

void gabe::logging::core::Logger::set_log_layout(const std::string &log_layout) {
    _log_layout = log_layout;
}

std::string gabe::logging::core::Logger::get_log_layout() {
    return _log_layout;
}

void gabe::logging::core::Logger::set_chained_logs(bool active) {
    _chained_logs = active;
}

bool gabe::logging::core::Logger::get_chained_logs() {
    return _chained_logs;
}

void gabe::logging::core::Logger::set_severity(const SeverityLevel &severity) {
    _severity = severity;
}

gabe::logging::SeverityLevel gabe::logging::core::Logger::get_severity() {
    return _severity;
}

void gabe::logging::core::Logger::set_logs_location(const std::string &location) {
    std::lock_guard<std::mutex> lock_guard(_log_mutex);
    _sink->set_file_directory(location);
    for (auto handler : _handlers) {
        handler.second->check_sink(_sink);
    }
}

std::string gabe::logging::core::Logger::get_logs_location() {
    return _sink->get_file_directory();
}

void gabe::logging::core::Logger::set_logs_file_name(const std::string &file_name) {
    std::lock_guard<std::mutex> lock_guard(_log_mutex);
    _sink->set_file_name(file_name + ".txt");
    for (auto handler : _handlers) {
        handler.second->check_sink(_sink);
    }
}

std::string gabe::logging::core::Logger::get_logs_file_name() {
    return _sink->get_file_name();
}

void gabe::logging::core::Logger::basic_config(const SeverityLevel &severity, const std::string &location, const std::string &file_name) {
    set_severity(severity);
    set_logs_location(location);
    set_logs_file_name(file_name);
}
