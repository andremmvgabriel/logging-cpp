#include <gabe/logging/logging.hpp>

static gabe::logging::Manager manager = gabe::logging::Manager();

void SET_LOGS_DIRECTORY(const std::string &path) {
    manager.set_logs_directory(path);
}

void LOG(const gabe::logging::SeverityLevel &severity, const std::string &message) {
    manager.log("main", severity, message);
}

void LOG(const std::string &logger_name, const gabe::logging::SeverityLevel &severity, const std::string &message) {
    manager.log(logger_name, severity, message);
}

void TRACE(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::TRACE, message);
}

void TRACE(const std::string &logger_name, const std::string &message) {
    manager.log(logger_name, gabe::logging::SeverityLevel::TRACE, message);
}

void DEBUG(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::DEBUG, message);
}

void DEBUG(const std::string &logger_name, const std::string &message) {
    manager.log(logger_name, gabe::logging::SeverityLevel::DEBUG, message);
}

void INFO(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::INFO, message);
}

void INFO(const std::string &logger_name, const std::string &message) {
    manager.log(logger_name, gabe::logging::SeverityLevel::INFO, message);
}

void WARNING(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::WARNING, message);
}

void WARNING(const std::string &logger_name, const std::string &message) {
    manager.log(logger_name, gabe::logging::SeverityLevel::WARNING, message);
}

void ERROR(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::ERROR, message);
}

void ERROR(const std::string &logger_name, const std::string &message) {
    manager.log(logger_name, gabe::logging::SeverityLevel::ERROR, message);
}

void FATAL(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::FATAL, message);
}

void FATAL(const std::string &logger_name, const std::string &message) {
    manager.log(logger_name, gabe::logging::SeverityLevel::FATAL, message);
}

/*
**
*/

gabe::logging::LoggerHandler GET_LOGGER(const std::string &logger_name) {
    return manager.get_logger(logger_name);
}
