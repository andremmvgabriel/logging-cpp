#include <gabe/logging/Manager.hpp>
#include <filesystem>

gabe::logging::Manager::Manager() : _default_logger("main"), _default_chained_logs(true), _default_severity(SeverityLevel::INFO), _default_log_layout("[%sev] %msg") {
    set_default_logs_directory(std::string(std::filesystem::current_path()));
}

gabe::logging::Manager::~Manager() {
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

std::string gabe::logging::Manager::_find_parent_logger_name(const std::string &logger_name) {
    std::size_t position = logger_name.find_last_of('.');
    return std::string(&logger_name[0], &logger_name[position]);
}

gabe::logging::LoggerHandler gabe::logging::Manager::get_logger(const std::string &logger_name) {
    if (_loggers.find(logger_name) == _loggers.end()) {
        core::Logger* parent = nullptr;
        
        if (logger_name.find('.') != -1) {
            std::size_t pos = logger_name.find_last_of('.');
            std::string parent_name = std::string(&logger_name[0], &logger_name[pos]);
            parent = get_logger(parent_name).ptr();
        }

        setup_logger(logger_name, parent);
    }

    return LoggerHandler(_loggers[logger_name]);
}

void gabe::logging::Manager::setup_logger(const std::string &logger_name, core::Logger* parent) {
    std::lock_guard<std::mutex> lock_guard(_manager_mutex);

    if (_loggers.find(logger_name) != _loggers.end()) return;

    core::Logger* logger = new core::Logger(_default_logs_directory, logger_name, _default_severity, parent);
    logger->set_chained_logs(_default_chained_logs);
    logger->set_log_layout(_default_log_layout);

    _loggers[logger_name] = logger;
}
