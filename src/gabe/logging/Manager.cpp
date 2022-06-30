#include <gabe/logging/Manager.hpp>
#include <filesystem>

gabe::logging::Manager::Manager() : _chained_logs(true) {
    set_logs_directory(std::string(std::filesystem::current_path()));
}

gabe::logging::Manager::~Manager() {
    for (auto logger : _loggers) {
        delete logger.second;
    }

    printf("All loggers deleted.\n");
}

void gabe::logging::Manager::set_logs_directory(const std::string &path) {
    _logs_directory = path;
}

void gabe::logging::Manager::set_chained_logs(bool active) {
    _chained_logs = active;
}

void gabe::logging::Manager::log(const std::string &logger_name, const SeverityLevel &severity, const std::string &message) {
    LoggerHandler logger = get_logger(logger_name);
    logger.log(severity, message);
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
    _manager_mutex.lock();

    if (_loggers.find(logger_name) != _loggers.end()) return;

    core::Logger* logger = new core::Logger(_logs_directory, logger_name, parent);
    logger->set_chained_logs(_chained_logs);

    _loggers[logger_name] = logger;

    _manager_mutex.unlock();
}
