#include <gabe/logging/logging.hpp>

static gabe::logging::Manager manager = gabe::logging::Manager();

gabe::logging::Manager* _get_internal_manager() {
    return &manager;
}

void SET_DEFAULT_LOGGER(const std::string &logger_name) {
    manager.set_default_logger(logger_name);
}

void SET_DEFAULT_CHAINED_LOGS(bool allow_chained) {
    manager.set_default_chained_logs(allow_chained);
}

void SET_DEFAULT_SEVERITY(const gabe::logging::SeverityLevel &severity) {
    manager.set_default_severity(severity);
}

void SET_DEFAULT_LOGS_DIRECTORY(const std::string &path) {
    manager.set_default_logs_directory(path);
}

gabe::logging::LoggerHandler GET_LOGGER(const std::string &logger_name) {
    return manager.get_logger(logger_name);
}
