#include <gabe/logging/logging.hpp>

static gabe::logging::Manager manager = gabe::logging::Manager();

void LOG(const gabe::logging::SeverityLevel &severity, const std::string &message) {
    manager.log("main", severity, message);
}

void TRACE(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::TRACE, message);
}

void DEBUG(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::DEBUG, message);
}

void INFO(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::INFO, message);
}

void WARNING(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::WARNING, message);
}

void ERROR(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::ERROR, message);
}

void FATAL(const std::string &message) {
    manager.log("main", gabe::logging::SeverityLevel::FATAL, message);
}

/*
**
*/

gabe::logging::LoggerHandler GET_LOGGER(const std::string &logger_name) {
    return manager.get_logger(logger_name);
}
