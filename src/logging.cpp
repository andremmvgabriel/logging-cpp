#include <logging.hpp>

logging::Logger::Logger() {}

logging::Logger::Logger(const logging::opts::Settings& settings) : _settings(settings) {}

logging::Logger::Logger(logging::Logger&& logger) {
    // Closes the log file if it is opened
    _log_file.close();

    // Moves the opened file from the given Logger object
    _log_file = std::move(logger._log_file);
}

logging::Logger& logging::Logger::operator = (logging::Logger&& logger) {
    // Closes the log file if it is opened
    if (_log_file.is_open()) { _log_file.close(); }

    // Moves the opened file from the given Logger object
    _log_file = std::move(logger._log_file);

    return *this;
}

logging::Logger::~Logger() {
    // Closes the log file if it is opened
    if (_log_file.is_open()) { _log_file.close(); }
}

void logging::Logger::init() {
    // Creates the logs directory (if it exists, this function does nothing)
    boost::filesystem::create_directory ( _settings.logs_dir );

    // Opens the log file
    if (!_open_log_file()) {
        std::runtime_error("Logger not initialized. File could not be opened.");
    } 

    // Updates the control variable
    _is_working = true;
}

bool logging::Logger::_open_log_file() {
    // Closes the log file if it is opened
    if (_log_file.is_open()) { _log_file.close(); }

    // Opens the log file
    _log_file = std::ofstream (
        _settings.logs_dir + _settings.file_name + std::to_string(++_files_counter) + ".txt", std::ios::out
    );

    return !_log_file.fail();
}