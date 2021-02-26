#pragma once

#include <iostream>
#include <unordered_map>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/current_function.hpp>

#include <ctime>
#include <chrono>

#include <mutex>

#include <type_traits>

#include "TextUtils.hpp"

#define __function__ BOOST_CURRENT_FUNCTION

namespace Logging
{
    enum class Severity
    {
        TRACE   = 1,
        DEBUG   = 2,
        INFO    = 4,
        WARNING = 8,
        ERROR   = 16,
        FATAL   = 32
    };

    namespace Edit
    {
        enum class Setting
        {
            LOGS_DIRECTORY,         // Directory to save logs
            FILE_NAME,              // Base name of the logs
            FILE_SIZE,              // Size of the log files
            LINE_SIZE,              // Size of each log line
            MULTIPLE_LINES,         // Allow a log to fill multiple lines
            TIME_TEMPLATE,          // Template of the timestamp
            LOG_TEMPLATE            // Template of the log
        };

        enum class LogTemplate
        {
            SEV_MSG         = 0,    // [Severity] Message
            TIME_SEV_MSG    = 1,    // [Timestamp][Severity] Message
            SEV_TIME_MSG    = 2,    // [Severity][Timestamp] Message
            SEV_MSG_TIME    = 4     // [Severity] Message [Timestamp]
        };
        
        enum class TimestampTemplate
        {
            TIME,                   // [hh:mm::ss]
            CALENDAR_TIME,          // [Week Month Day][hh::mm::ss]
            CALENDAR_YEAR_TIME,     // [Week Month Day Year][hh::mm::ss]
        };

        enum class TextType
        {
            HEADER,
            SUB_HEADER,
            NORMAL
        };

        struct Settings
        {
            std::string logs_directory;
            std::string file_name;
            int max_file_size;
            int max_line_size;
            bool allow_multiple_line_logs;
            TimestampTemplate timestamp_template;
            LogTemplate log_template;
        };
    } // namespace Edit

    namespace Utils
    {
        namespace Dictionary
        {
            static std::unordered_map<int, std::string> months {
                {0, "Jan"},
                {1, "Feb"},
                {2, "Mar"},
                {3, "Apr"},
                {4, "May"},
                {5, "Jun"},
                {6, "Jul"},
                {7, "Ago"},
                {8, "Sep"},
                {9, "Oct"},
                {10, "Nov"},
                {11, "Dec"}
            };

            static std::unordered_map<int, std::string> week_days {
                {0, "Sun"},
                {1, "Mon"},
                {2, "Tue"},
                {3, "Wed"},
                {4, "Thu"},
                {5, "Fri"},
                {6, "Sat"}
            };

            static std::unordered_map<Severity, std::string> severity_levels {
                {Severity::TRACE,   "[ trace ]"},
                {Severity::DEBUG,   "[ debug ]"},
                {Severity::INFO,    "[ info  ]"},
                {Severity::WARNING, "[warning]"},
                {Severity::ERROR,   "[ error ]"},
                {Severity::FATAL,   "[ fatal ]"}
            };

            static std::unordered_map<Edit::LogTemplate, std::string> log_templates {
                {Edit::LogTemplate::SEV_MSG, "[Severity] Message"},
                {Edit::LogTemplate::TIME_SEV_MSG, "[Time][Severity] Message"},
                {Edit::LogTemplate::SEV_TIME_MSG, "[Severity][Time] Message"},
                {Edit::LogTemplate::SEV_MSG_TIME, "[Severity] Message [Time]"}
            };

            static std::unordered_map<Edit::TimestampTemplate, std::string> timestamp_templates {
                {Edit::TimestampTemplate::TIME, "[hh::mm::ss]"},
                {Edit::TimestampTemplate::CALENDAR_TIME, "[week month day][hh::mm::ss]"},
                {Edit::TimestampTemplate::CALENDAR_YEAR_TIME, "[week month day year][hh::mm::ss]"}
            };
        } // namespace Dictionary        
    } // namespace Utils    
    
    class Logger
    {
    private:
        bool isWorking = false;
        std::mutex logMutex;

        std::ofstream log_file;
        int counter_log_files = 0;

        Edit::Settings defaultSettings = {
            "logs/",                        // Logs directory
            "log_file",                     // Logs base file name
            5000000,                        // Max file size (in bytes)
            66,                             // Max line size - 66 characters
            true,                           // Allow logs for multiple lines
            Edit::TimestampTemplate::TIME,  // Time only timestamp
            Edit::LogTemplate::SEV_MSG,     // Log as Severity + Message
        };
    
    private:
        void checkLogsDirectory();
        bool openLogFile();
        void checkLogFileSize();

        std::string makeTimestamp();

        void write_header_log(const std::string &initiation, std::string message, const std::string &termination);

        void write_sub_header_log(const std::string &initiation, std::string message, const std::string &termination);

        void write_normal_log(const std::string &initiation, std::string message, const std::string &termination);

    public:
        Logger();
        ~Logger();

        // Disable copy constructor
        Logger(const Logger& logger) = delete;

        // Disable copy assignment
        Logger& operator= (const Logger& logger) = delete;

        // New copy constructor
        Logger (Logger&& logger) {
            log_file.close();
            log_file = std::move(logger.log_file);
        }

        // New copy assignment
        Logger& operator= (Logger&& logger) {
            log_file.close();
            log_file = std::move(logger.log_file);

            return *this;
        }

        void init();

        // Overload setSetting for strings
        void setSetting(Edit::Setting setting, const std::string &value);

        // Overload setSetting for int / bool
        void setSetting(Edit::Setting setting, int value);

        // Overload to timestamp template
        void setSetting(Edit::Setting setting, Edit::TimestampTemplate value);

        // Overload to log template
        void setSetting(Edit::Setting setting, Edit::LogTemplate value);

        void setSettings(Edit::Settings settings);

        template <Edit::TextType TT = Edit::TextType::NORMAL>
        void write_log(Severity severity, const std::string &message)
        {
            if (isWorking) {
                // Locks with the mutex
                std::lock_guard<std::mutex> lock(logMutex);

                // Creates the three log parts
                std::string initiation, termination;

                // Checks if the log template has the time in the beginning
                if (defaultSettings.log_template == Logging::Edit::LogTemplate::TIME_SEV_MSG) {
                    // Adds the timestamp
                    initiation += makeTimestamp();
                }

                // Adds the severity level
                initiation += Utils::Dictionary::severity_levels.at(severity);

                // Checks if the log has the time after the severity
                if (defaultSettings.log_template == Logging::Edit::LogTemplate::SEV_TIME_MSG) {
                    // Adds the timestamp
                    initiation += makeTimestamp();
                }

                // Adds a space to the initiation
                initiation += " ";

                // Checks if the log has the time after the message
                if (defaultSettings.log_template == Logging::Edit::LogTemplate::SEV_MSG_TIME) {
                    // Adds the timestamp
                    termination += " " + makeTimestamp();
                }

                // Adds the end line to the termination
                termination += "\n";

                // Writes based on the Text Type that the user wants
                if (TT == Edit::TextType::HEADER) { write_header_log(initiation, message, termination); }
                else if (TT == Edit::TextType::SUB_HEADER) { write_sub_header_log(initiation, message, termination); }
                else if (TT == Edit::TextType::NORMAL) { write_normal_log(initiation, message, termination); }

                // After logging, check file size
                checkLogFileSize();
            }
        }
    };
} // namespace Logging

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