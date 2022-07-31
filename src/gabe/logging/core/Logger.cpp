#include <gabe/logging/core/Logger.hpp>

/*
Internal Formatters
*/

gabe::logging::core::Logger::SeverityFormatter::SeverityFormatter() : Formatter("SeverityFormatter", "%sev") {}

void gabe::logging::core::Logger::SeverityFormatter::set_severity(const SeverityLevel &severity) { _severity = severity; }

std::string gabe::logging::core::Logger::SeverityFormatter::_format() {
    return fmt::format("{:^7}", _formatting[_severity]);
}



gabe::logging::core::Logger::MessageFormatter::MessageFormatter() : Formatter("MessageFormatter", "%msg") {}

void gabe::logging::core::Logger::MessageFormatter::set_message(const std::string &message) { _message = message; }

std::string gabe::logging::core::Logger::MessageFormatter::_format() {
    return _message;
}

void gabe::logging::core::Logger::MessageFormatter::format(std::string &message) {
    // Copies the given message
    std::string message_copy = message;

    // Formats the message as expected
    Formatter::format(message);

    // Adds the message to the end of the formatting in case the formatting is is not present
    if (message == message_copy) {
        message = message + " " + _message;
    }
}



/*
Logger
*/

gabe::logging::core::Logger::Logger() : _severity(SeverityLevel::INFO), _parent(nullptr) {
    // Creates the sink
    _sink = new Sink("", "log.txt");

    // Setus the internal formatters
    _setup_internal_formatters();
}

gabe::logging::core::Logger::Logger(const std::string &location, const std::string &name, Logger* parent) : _severity(SeverityLevel::INFO), _parent(parent) {
    // Filters the log name
    std::string filtered_name = _filter_logger_name(name);

    // Creates the sink
    _sink = new Sink(location, filtered_name + ".txt");

    // Setus the internal formatters
    _setup_internal_formatters();
}

gabe::logging::core::Logger::Logger(const std::string &location, const std::string &name, const gabe::logging::SeverityLevel &severity) : _severity(severity), _parent(nullptr) {
    // Filters the log name
    std::string filtered_name = _filter_logger_name(name);

    // Creates the sink
    _sink = new Sink(location, filtered_name + ".txt");

    // Setus the internal formatters
    _setup_internal_formatters();
}

gabe::logging::core::Logger::Logger(const std::string &location, const std::string &name, const gabe::logging::SeverityLevel &severity, Logger *parent) : _severity(severity), _parent(parent) {
    // Filters the log name
    std::string filtered_name = _filter_logger_name(name);

    // Creates the sink
    _sink = new Sink(location, filtered_name + ".txt");

    // Setus the internal formatters
    _setup_internal_formatters();
}

gabe::logging::core::Logger::~Logger() {
    _delete_sink();
    _delete_handlers();
    _delete_formatters();
    _parent = nullptr;
}

std::string gabe::logging::core::Logger::_filter_logger_name(std::string name) {
    // Replaces every "." found with a "-"
    std::size_t position = name.find(".");
    while(position != -1) {
        name[position] = '-';
        position = name.find(".");
    }

    return name;
}

void gabe::logging::core::Logger::_setup_internal_formatters() {
    add_formatter(SeverityFormatter());
    add_formatter(MessageFormatter());
}

void gabe::logging::core::Logger::_delete_sink() {
    // Makes sure to flush before deleting the sink
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
    // Locks the mutex
    std::lock_guard<std::mutex> lock_guard(_log_mutex);

    // Does not log if the severity level is not enough
    if ( (uint8_t)severity < (uint8_t)_severity ) return;

    // Starts the message to log with the log layout
    std::string final_log_message = _log_layout;

    // Formatters
    dynamic_cast<SeverityFormatter*>(_formatters["SeverityFormatter"])->set_severity(severity);

    dynamic_cast<MessageFormatter*>(_formatters["MessageFormatter"])->set_message(message);

    for (auto formatter : _formatters) {
        formatter.second->format(final_log_message);
    }

    final_log_message += "\n";

    // Handlers
    _process_handlers(final_log_message);

    // Sink management
    if (_sink->should_flush(message)) {
        _sink->flush();
    }
    
    _sink->sink_in(final_log_message);

    // Also logs into parent if existent, and allowed
    if (_parent && _chained_logs) _parent->log(severity, message);
}

void gabe::logging::core::Logger::_process_handlers(const std::string &message) {
    // Control variable to know if any handler was triggered
    bool needs_rotation = false;

    // Caches the current file name
    std::string file_name = _sink->get_file_name();

    // Checks all the handlers
    for (auto handler : _handlers) {
        if (handler.second->evaluate(_sink, message)) {
            file_name = handler.second->create_handled_file_name(file_name);
            needs_rotation = true;
        }
    }

    // Rotates the file if needed
    if (needs_rotation) {
        _sink->rotate_file(file_name);
    }
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
    // Logs the mutex
    std::lock_guard<std::mutex> lock_guard(_log_mutex);

    // Changes the file directory
    _sink->set_file_directory(location);
    
    // Makes all the handlers check the sink
    for (auto handler : _handlers) {
        handler.second->check_sink(_sink);
    }
}

std::string gabe::logging::core::Logger::get_logs_location() {
    return _sink->get_file_directory();
}

void gabe::logging::core::Logger::set_logs_file_name(const std::string &file_name) {
    // Logs the mutex
    std::lock_guard<std::mutex> lock_guard(_log_mutex);

    // Filter the new logger name
    std::string filtered_name = _filter_logger_name(file_name);

    // Changes the file name
    _sink->set_file_name(filtered_name + ".txt");

    // Makes all the handlers check the sink
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
