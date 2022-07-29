#include <gabe/logging/Manager.hpp>
#include <filesystem>

gabe::logging::Manager::Manager() : _default_logger("main"), _default_chained_logs(true), _default_severity(SeverityLevel::INFO), _default_log_layout("[%sev] %msg") {
    // Sets the default logs directory as the current path of the executable
    set_default_logs_directory(std::string(std::filesystem::current_path()));
}

std::string gabe::logging::Manager::_get_parent_logger_name(const std::string &logger_name) {
    // Gets the position of the last dot
    std::size_t position = logger_name.find_last_of('.');

    // Creates the name of the parent logger
    return std::string(&logger_name[0], &logger_name[position]);
}

gabe::logging::Manager::~Manager() {
    // Deletes all the created loggers
    for (auto logger : _loggers) {
        delete logger.second;
    }
}

void gabe::logging::Manager::set_default_logger(const std::string &logger_name) {
    _default_logger = logger_name;
}

void gabe::logging::Manager::set_default_chained_logs(bool allow_chained) {
    _default_chained_logs = allow_chained;
}

void gabe::logging::Manager::set_default_severity(const SeverityLevel &severity) {
    _default_severity = severity;
}

void gabe::logging::Manager::set_default_logs_directory(const std::string &path) {
    _default_logs_directory = path;
}

void gabe::logging::Manager::set_default_log_layout(const std::string &log_layout) {
    _default_log_layout = log_layout;
}

gabe::logging::LoggerHandler gabe::logging::Manager::get_logger(const std::string &logger_name) {
    // Checks if the logger needs to be created
    if (_loggers.find(logger_name) == _loggers.end()) {
        core::Logger* parent = nullptr;
        
        // Checks if the logger name contains any hierarchy
        if (logger_name.find('.') != -1) {
            // Gets the logger parent name
            std::string parent_name = _get_parent_logger_name(logger_name);

            // Gets the logger object pointer
            parent = get_logger(parent_name).ptr();
        }

        // Creates the logger with its parent
        setup_logger(logger_name, parent);
    }

    // Returns the logger as a logger handler object
    return LoggerHandler(_loggers[logger_name]);
}

void gabe::logging::Manager::setup_logger(const std::string &logger_name, core::Logger* parent) {
    // Locks the function with the mutex
    std::lock_guard<std::mutex> lock_guard(_manager_mutex);

    // Safety check - Exists the function if the logger already exists
    if (_loggers.find(logger_name) != _loggers.end()) return;

    // Creates a pointer of the target logger
    core::Logger* logger = new core::Logger(_default_logs_directory, logger_name, _default_severity, parent);

    // Sets the default settings into the logger 
    logger->set_chained_logs(_default_chained_logs);
    logger->set_log_layout(_default_log_layout);

    // Adds the logger into the map
    _loggers[logger_name] = logger;
}
