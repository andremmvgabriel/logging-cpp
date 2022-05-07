#include <gabe/logging/core/Logger.hpp>

gabe::logging::core::Logger::Logger() : _severity(SeverityLevel::INFO) {
    _open_log_file();
}

gabe::logging::core::Logger::Logger(const gabe::logging::SeverityLevel &severity) : _severity(severity) {
    _open_log_file();
}

gabe::logging::core::Logger::~Logger() {
    if (_log_file.is_open()) _log_file.close();

    for (auto handler : _handlers) {
        delete handler.second;
    }
}

void gabe::logging::core::Logger::log(const gabe::logging::SeverityLevel &severity, const std::string &message) {
    if ( (uint8_t)severity < (uint8_t)_severity ) return;
    _log_file.write( message.c_str(), message.size() );
}

void gabe::logging::core::Logger::_open_log_file() {
    if (_log_file.is_open()) return;

    _log_file = std::ofstream(
        "log_file.txt",
        std::ios::out | std::ios::app
    );
}
