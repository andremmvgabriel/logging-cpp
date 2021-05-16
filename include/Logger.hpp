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

#define __function__ BOOST_CURRENT_FUNCTION

namespace TextUtils
{
    namespace Alignment
    {
        void left(std::string &msg, const int width);
        void right(std::string &msg, const int width);
        void center(std::string &msg, const int width);
        void justify(std::string &msg, const int width);
    } // namespace Alignment
} // namespace TextUtils

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

        /*
        Settings order:
        1. Logs directory;
        2. File name;
        3. File size;
        4. Line size;
        5. Enable multiple lines;
        6. Time template;
        7. Log template.
        */
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
