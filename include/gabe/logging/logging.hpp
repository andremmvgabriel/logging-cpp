#include <string>

#include <gabe/logging/Manager.hpp>
#include <gabe/logging/SeverityLevel.hpp>

static gabe::logging::Manager manager;

void log(const gabe::logging::SeverityLevel &severity, const std::string &log_message);
