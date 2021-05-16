#include <Logger.hpp>

void TextUtils::Alignment::left(std::string &msg, const int width) {
    if (msg.size() <= width) {
        int final_size = width - msg.size();
        for (int i = 0; i < final_size; i++) {
            msg.push_back(' ');
        }
    }
    else {
        int remove_size = msg.size() - width - 1;
        for (int i = remove_size; i >= 0; i--) {
            msg.pop_back();
        }
    }
}

void TextUtils::Alignment::right(std::string &msg, const int width) {
    if (msg.size() <= width) {
        int final_size = width - msg.size();
        std::string decoy;
        for (int i = 0; i < final_size; i++) {
            decoy.push_back(' ');
        }
        msg.insert(msg.begin(), decoy.begin(), decoy.end());
    }
    else {
        int remove_size = msg.size() - width - 1;
        for (int i = remove_size; i >= 0; i--) {
            msg.pop_back();
        }
    }
}

void TextUtils::Alignment::center(std::string &msg, const int width) {
    if (msg.size() <= width) {
        int decoy1_size = (width - msg.size())/2;
        int decoy2_size = width - msg.size() - decoy1_size;
        std::string decoy1;
        for (int i = 0; i < decoy1_size; i++) { decoy1.push_back(' '); }
        msg.insert(msg.begin(), decoy1.begin(), decoy1.end());
        for (int i = 0; i < decoy2_size; i++) { msg.push_back(' '); }
    }
    else {
        int remove_size = msg.size() - width - 1;
        for (int i = remove_size; i >= 0; i--) {
            msg.pop_back();
        }
    }
}

void TextUtils::Alignment::justify(std::string &msg, const int width) {}







Logging::Logger::Logger() {}

Logging::Logger::~Logger() {
    if (log_file.is_open()) { log_file.close(); }
}

void Logging::Logger::init() {
    // Checks the logs directory
    checkLogsDirectory();

    // Opens the log file
    if (!openLogFile()) { std::cerr << "> Logger not initialized. Log file could not be opened." << std::endl; return; }

    // Logger correctly initialized
    isWorking = true;
}

void Logging::Logger::checkLogsDirectory() {
    // Removes any previous logs, if any exist
    //boost::filesystem::remove_all(defaultSettings.logs_directory);

    // Creates the logs directory
    boost::filesystem::create_directory(defaultSettings.logs_directory);
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

void Logging::Logger::setSetting(Edit::Setting setting, const std::string &value) {
    if (isWorking) {
        throw std::runtime_error("You cannot change a setting once the logger was initiated.");
    }

    switch (setting)
    {
    case Edit::Setting::LOGS_DIRECTORY:
        // Change the Log Directory setting
        defaultSettings.logs_directory = value;

        break;
    
    case Edit::Setting::FILE_NAME:
        // Change the Log Directory setting
        defaultSettings.file_name = value;

        break;
    
    default:
        std::cerr << "> The input logger setting was not recognized. Default / previous setting will remain active." << std::endl;
        
        break;
    }
}

void Logging::Logger::setSetting(Edit::Setting setting, int value){
    if (isWorking) {
        throw std::runtime_error("You cannot change the settings once the logger was initiated.");
    }

    switch (setting)
    {
    case Edit::Setting::FILE_SIZE:
        // Change the Log Directory setting
        defaultSettings.max_file_size = value;

        break;
    
    case Edit::Setting::LINE_SIZE:
        // Change the Log Directory setting
        defaultSettings.max_line_size = value;

        break;

    case Edit::Setting::MULTIPLE_LINES:
        // Change the Log Directory setting
        defaultSettings.allow_multiple_line_logs = (bool)value;

        break;

    case Edit::Setting::LOG_TEMPLATE:
        // Change the Log Directory setting
        defaultSettings.log_template = (Edit::LogTemplate)value;

        break;
    
    case Edit::Setting::TIME_TEMPLATE:
        // Change the Log Directory setting
        defaultSettings.timestamp_template = (Edit::TimestampTemplate)value;

        break;
    
    default:
        std::cerr << "> The input logger setting was not recognized. Default / previous setting will remain active." << std::endl;
        
        break;
    }
}

void Logging::Logger::setSetting(Edit::Setting setting, Edit::TimestampTemplate value) { setSetting(setting, (int)value); }

void Logging::Logger::setSetting(Edit::Setting setting, Edit::LogTemplate value) { setSetting(setting, (int)value); }

void Logging::Logger::setSettings(Edit::Settings settings) {
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
    if (defaultSettings.log_template == Logging::Edit::LogTemplate::SEV_MSG) { return ""; }

    // Gets the time since epoch
    std::time_t time_since_epoch = std::time(nullptr);

    // Gets the local time
    std::tm *tm = std::localtime(&time_since_epoch);

    // Creates the timestamp string, that will be output
    std::string timestamp;

    // Opens the timestamp bracket
    timestamp += "[";

    bool calendar = false, year = false;

    if (defaultSettings.timestamp_template == Edit::TimestampTemplate::CALENDAR_YEAR_TIME) {
        // Adds the Week day to the timestamp
        timestamp += Utils::Dictionary::week_days.at(tm->tm_wday);

        // Adds a space
        timestamp += " ";

        // Adds the Month to the timestamp
        timestamp += Utils::Dictionary::months.at(tm->tm_mon);

        // Adds a space
        timestamp += " ";

        // Adds the Day to the timestamp
        timestamp += (tm->tm_mday < 10 ? "0" + std::to_string(tm->tm_mday) : std::to_string(tm->tm_mday));

        // Adds a space
        timestamp += " ";

        // Adds the year
        timestamp += std::to_string(tm->tm_year + 1900);
    }
    else if (defaultSettings.timestamp_template == Edit::TimestampTemplate::CALENDAR_TIME) {
        // Adds the Week day to the timestamp
        timestamp += Utils::Dictionary::week_days.at(tm->tm_wday);

        // Adds a space
        timestamp += " ";

        // Adds the Month to the timestamp
        timestamp += Utils::Dictionary::months.at(tm->tm_mon);

        // Adds a space
        timestamp += " ";

        // Adds the Day to the timestamp
        timestamp += (tm->tm_mday < 10 ? "0" + std::to_string(tm->tm_mday) : std::to_string(tm->tm_mday));
    }

    // Closes and opens a bracket, if the user wanted the calendar
    if (defaultSettings.timestamp_template != Edit::TimestampTemplate::TIME) { timestamp += "]["; }

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

void Logging::Logger::write_header_log(const std::string &initiation, std::string message, const std::string &termination) {
    // Creates the extra strings needed for the header
    std::string empty_message = initiation;
    std::string separator_message = initiation;

    // Fills the extra strings with content
    for (int i = 0; i < defaultSettings.max_line_size; i++) {
        empty_message.push_back(' ');
        separator_message.push_back('*');
    }

    // Concludes the extra string with the termination
    empty_message += termination;
    separator_message += termination;

    // Logs the empty message followed by the separator
    log_file.write(empty_message.c_str(), empty_message.size());
    log_file.write(separator_message.c_str(), separator_message.size());

    // Writes the log message(s)
    bool writting = true;
    while (writting) {
        // Creates the current log
        std::string cur_log = initiation;

        // Adds the initiation delimiter
        cur_log += "* ";

        // Calculates the size that has to be removed
        int size_to_remove = message.size() + 4 - defaultSettings.max_line_size;

        // Checks if there is anything to be removed
        if (size_to_remove > 0) {
            if (!defaultSettings.allow_multiple_line_logs) {
                // Removes the unwanted part of the message
                message.erase( message.end() - 6 - size_to_remove, message.end() );

                // Adds the message to the log
                cur_log += message + " (...)";

                // Changes the writting variable state
                writting = false;
            }
            else {
                // If the message starts with a space, remove it
                if (message[0] == ' ') { message.erase(message.begin()); }

                // Gets the current part of the message
                std::string cur_part(message.begin(), message.begin() + defaultSettings.max_line_size - 4);

                // Removes the unwanted part of the message
                message.erase(message.begin(), message.begin() + defaultSettings.max_line_size - 4);

                // Adds the message to the log
                cur_log += cur_part;
            }
        }
        else {
            // If the message starts with a space, remove it
            if (message[0] == ' ') { message.erase(message.begin()); }
                
            // Centers the text
            TextUtils::Alignment::center(message, defaultSettings.max_line_size - 4);

            // Adds the message to the log
            cur_log += message;

            // Changes the writting variable state
            writting = false;
        }

        // Adds the termination delimiter
        cur_log += " *";

        // Adds the termination to the log
        cur_log += termination;

        // Writes the log
        log_file.write(cur_log.c_str(), cur_log.size());
    }

    // Logs the separator to conclude the header
    log_file.write(separator_message.c_str(), separator_message.size());
}

void Logging::Logger::write_sub_header_log(const std::string &initiation, std::string message, const std::string &termination) {
    // Writes the log message(s)
    bool writting = true;
    while (writting) {
        // Creates the current log
        std::string cur_log = initiation;

        // Adds the initiation delimiter
        cur_log += "~~~ ";

        // Calculates the size that has to be removed
        int size_to_remove = message.size() + 8 - defaultSettings.max_line_size;

        // Checks if there is anything to be removed
        if (size_to_remove > 0) {
            if (!defaultSettings.allow_multiple_line_logs) {
                // Removes the unwanted part of the message
                message.erase( message.end() - 6 - size_to_remove, message.end() );

                // Adds the message to the log
                cur_log += message + " (...)";

                // Changes the writting variable state
                writting = false;
            }
            else {
                // If the message starts with a space, remove it
                if (message[0] == ' ') { message.erase(message.begin()); }
                
                // Gets the current part of the message
                std::string cur_part(message.begin(), message.begin() + defaultSettings.max_line_size - 8);

                // Removes the unwanted part of the message
                message.erase(message.begin(), message.begin() + defaultSettings.max_line_size - 8);

                // Adds the message to the log
                cur_log += cur_part;
            }
        }
        else {
            // If the message starts with a space, remove it
            if (message[0] == ' ') { message.erase(message.begin()); }
                
            // Centers the text
            TextUtils::Alignment::center(message, defaultSettings.max_line_size - 8);

            // Adds the message to the log
            cur_log += message;

            // Changes the writting variable state
            writting = false;
        }

        // Adds the termination delimiter
        cur_log += " ~~~";

        // Adds the termination to the log
        cur_log += termination;

        // Writes the log
        log_file.write(cur_log.c_str(), cur_log.size());
    }
}

void Logging::Logger::write_normal_log(const std::string &initiation, std::string message, const std::string &termination) {
    // Writes the log message(s)
    bool writting = true;
    while (writting) {
        // Creates the current log
        std::string cur_log = initiation;

        // Calculates the size that has to be removed
        int size_to_remove = message.size() - defaultSettings.max_line_size;

        // Checks if there is anything to be removed
        if (size_to_remove > 0) {
            if (!defaultSettings.allow_multiple_line_logs) {
                // Removes the unwanted part of the message
                message.erase( message.end() - 6 - size_to_remove, message.end() );

                // Adds the message to the log
                cur_log += message + " (...)";

                // Changes the writting variable state
                writting = false;
            }
            else {
                // If the message starts with a space, remove it
                if (message[0] == ' ') { message.erase(message.begin()); }
                
                // Gets the current part of the message
                std::string cur_part(message.begin(), message.begin() + defaultSettings.max_line_size);

                // Removes the unwanted part of the message
                message.erase(message.begin(), message.begin() + defaultSettings.max_line_size);

                // Adds the message to the log
                cur_log += cur_part;
            }
        }
        else {
            // If the message starts with a space, remove it
            if (message[0] == ' ') { message.erase(message.begin()); }
                
            // Centers the text
            TextUtils::Alignment::left(message, defaultSettings.max_line_size);

            // Adds the message to the log
            cur_log += message;

            // Changes the writting variable state
            writting = false;
        }

        // Adds the termination to the log
        cur_log += termination;

        // Writes the log
        log_file.write(cur_log.c_str(), cur_log.size());
    }
}