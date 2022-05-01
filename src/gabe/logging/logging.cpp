#include <gabe/logging/logging.hpp>

void log(const gabe::logging::SeverityLevel &severity_level, const std::string &log_message) {
    manager.log("main", severity_level, log_message);
}
