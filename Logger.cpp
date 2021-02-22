#include "Logger.hpp"

Logging::Logger::Logger() {}

Logging::Logger::~Logger() {
    if (log_file.is_open()) { log_file.close(); }
}

void Logging::Logger::init() {
    // Checks the logs directory
    if (!checkLogsDirectory()) { std::cerr << "> Logger not initialized. Could not create the directory for the log files." << std::endl; return; }

    // Opens the log file
    if (!openLogFile()) { std::cerr << "> Logger not initialized. Log file could not be opened." << std::endl; return; }

    // Logger correctly initialized
    isWorking = true;
}

bool Logging::Logger::checkLogsDirectory() {
    // Removes any previous logs, if any exist
    boost::filesystem::remove_all(defaultSettings.logs_directory);

    // Creates the logs directory
    return boost::filesystem::create_directory(defaultSettings.logs_directory);
}

bool Logging::Logger::openLogFile() {
    // Closes the previous log file, if is opened
    if (log_file.is_open()) { log_file.close(); }

    // Opens the file
    log_file = std::ofstream (
        defaultSettings.logs_directory +
        defaultSettings.file_name +
        std::to_string(++counter_log_files) +
        ".txt", std::ios::out
    );

    return !log_file.fail();
}

void Logging::Logger::setSettings(Logging::Edit::Setting setting) {}

void Logging::Logger::setSettings(Logging::Edit::Settings settings) {
    defaultSettings = settings;
}

void Logging::Logger::checkLogFileSize() {
    // Checks if the current log file as already achieved the maximum size
    if (log_file.tellp() >= defaultSettings.max_file_size) {
        // Opens a new log file
        if (!openLogFile()) { std::cerr << "> Logger stopped working. New log file could not be opened." << std::endl; isWorking = false; return; }
    }
}

std::string Logging::Logger::makeTimestamp() {
    // If the user does not want a timestamp
    if (defaultSettings.timestamp_template == Logging::Edit::TimestampTemplate::NONE) { return ""; }

    // Gets the time since epoch
    std::time_t time_since_epoch = std::time(nullptr);

    // Gets the local time
    std::tm *tm = std::localtime(&time_since_epoch);

    // Creates the timestamp string, that will be output
    std::string timestamp;

    // Opens the timestamp bracket
    timestamp += "[";

    //Logging::Edit::TimestampTemplate::CALENDAR_YEAR_TIME
    
    bool calendar = false, year = false;

    if (defaultSettings.timestamp_template == Logging::Edit::TimestampTemplate::CALENDAR_YEAR_TIME) {
        // Adds the Week day to the timestamp
        timestamp += Logging::Utils::Dictionary::week_days.at(tm->tm_wday);

        // Adds a space
        timestamp += " ";

        // Adds the Month to the timestamp
        timestamp += Logging::Utils::Dictionary::months.at(tm->tm_mon);

        // Adds a space
        timestamp += " ";

        // Adds the Day to the timestamp
        timestamp += (tm->tm_mday < 10 ? "0" + std::to_string(tm->tm_mday) : std::to_string(tm->tm_mday));

        // Adds a space
        timestamp += " ";

        // Adds the year
        timestamp += std::to_string(tm->tm_year + 1900);
    }
    else if (defaultSettings.timestamp_template == Logging::Edit::TimestampTemplate::CALENDAR_TIME) {
        // Adds the Week day to the timestamp
        timestamp += Logging::Utils::Dictionary::week_days.at(tm->tm_wday);

        // Adds a space
        timestamp += " ";

        // Adds the Month to the timestamp
        timestamp += Logging::Utils::Dictionary::months.at(tm->tm_mon);

        // Adds a space
        timestamp += " ";

        // Adds the Day to the timestamp
        timestamp += (tm->tm_mday < 10 ? "0" + std::to_string(tm->tm_mday) : std::to_string(tm->tm_mday));
    }

    // Closes and opens a bracket, if the user wanted the calendar
    timestamp += "][";

    // Adds the hour
    if (tm->tm_hour < 10) { timestamp += "0"; }
    timestamp += std::to_string(tm->tm_hour);

    // Adds a delimiter
    timestamp += ":";

    // Adds the minutes
    if (tm->tm_min < 10) { timestamp += "0"; }
    timestamp += std::to_string(tm->tm_min); 

    // Adds a delimiter
    timestamp += ":";

    // Adds the seconds
    if (tm->tm_sec < 10) { timestamp += "0"; }
    timestamp += std::to_string(tm->tm_sec);

    // Closes the timestamp bracket
    timestamp += "]";

    return timestamp;
}

void Logging::Logger::log_info(std::string message) {
    if (isWorking) {
        // Creates the three log parts
        std::string initiation, middle, termination;

        // Checks if the log template has the time in the beginning
        if (defaultSettings.log_template == Logging::Edit::LogTemplate::TIME_SEV_MSG) {
            // Adds the timestamp
            initiation += makeTimestamp();
        }

        // Adds the severity level
        initiation += "[info]";

        // Checks if the log has the time after the severity
        if (defaultSettings.log_template == Logging::Edit::LogTemplate::SEV_TIME_MSG) {
            // Adds the timestamp
            initiation += makeTimestamp();
        }

        // Checks if the log has the time after the message
        if (defaultSettings.log_template == Logging::Edit::LogTemplate::SEV_MSG_TIME) {
            // Adds the timestamp
            termination += " " + makeTimestamp();
        }

        // Adds the end line
        termination += "\n";

        // Makes sure the user allows multiple lines for a single log
        if (defaultSettings.allow_multiple_line_logs) {
            // Writes the logs
            int writting = true;
            while (writting) {
                std::string curLog = initiation;

                // Adds a separation
                curLog += " ";

                if (message.size() > defaultSettings.max_line_size) {
                    curLog.insert(curLog.end(), message.begin(), message.begin() + defaultSettings.max_line_size);

                    message.erase(message.begin(), message.begin() + defaultSettings.max_line_size);
                }
                else {
                    TextUtils::Alignment::left(message, defaultSettings.max_line_size);
                    curLog += message;
                    writting = false;
                }

                curLog += termination;

                log_file.write(curLog.c_str(), curLog.size());
            }
        }
        else {
            std::string log = initiation;

            // Checks if the message has more size than allowed
            if (message.size() > defaultSettings.max_line_size) {
                int size_to_remove = message.size() - defaultSettings.max_line_size;

                message.erase(message.end() - 1 - 5 - size_to_remove, message.end());

                log += " " + message + " (...)";
            }
            else {
                TextUtils::Alignment::left(message, defaultSettings.max_line_size);
                log += " " + message;
            }

            log += termination;

            log_file.write(log.c_str(), log.size());
        }        
    }
}
