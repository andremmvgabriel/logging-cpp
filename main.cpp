#include <iostream>
#include <unordered_map>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/current_function.hpp>

#include <ctime>

#include <type_traits>

#define __function__ BOOST_CURRENT_FUNCTION

enum class Severity
{
    TRACE   = 1,
    DEBUG   = 2,
    INFO    = 4,
    WARNING = 8,
    ERROR   = 16,
    FATAL   = 32
};

enum LoggingPattern
{
    SEV_MSG         = 0,
    TIME_SEV_MSG    = 1,
    SEV_TIME_MSG    = 2,
    SEV_MSG_TIME    = 4
};

enum Time
{
    NONE    = 0,
    TIME    = 1,
    DAY     = 2,
    WEEK    = 4,
    MONTH   = 8,
    YEAR    = 16
};

inline Time operator & (Time time1, Time time2) { 
    using T = std::underlying_type_t<Time>;
    return static_cast<Time>( static_cast<T>(time1) & static_cast<T>(time2) );
}

inline Time operator &= (Time time1, Time time2) { return (time1 & time2); }

inline Time operator | (Time time1, Time time2) { 
    using T = std::underlying_type_t<Time>;
    return static_cast<Time>( static_cast<T>(time1) | static_cast<T>(time2) );
}

inline Time operator |= (Time time1, Time time2) { return (time1 & time2); }

std::unordered_map<int, std::string> months_map {
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

std::unordered_map<int, std::string> weeks_map {
    {0, "Sun"},
    {1, "Mon"},
    {2, "Tue"},
    {3, "Wed"},
    {4, "Thu"},
    {5, "Fri"},
    {6, "Sat"}
};

namespace TextUtils
{
    namespace Alignment
    {
        void left(std::string &msg, const int width) {
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

        void right(std::string &msg, const int width) {
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

        void center(std::string &msg, const int width) {
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

        void justify(std::string &msg, const int width) {

        }
    } // namespace Alignment
} // namespace TextUtils

class Logger
{
private:
    struct DefaultSettings
    {
        std::string logs_directory;
        int max_file_size;
        int max_line_size;
        Time time_representation;
        LoggingPattern logging_pattern;
    };

public:
    enum class Settings
    {
        LOG_DIR     = 0,
        FILE_SIZE   = 1,
        LINE_SIZE   = 2,
        TIME_REP    = 4,
        LOG_PATT    = 8
    };

private:
    std::ofstream file;

    std::unordered_map<Severity, std::ofstream> log_files;

    std::unordered_map<Severity, std::string> severity_levels {
        {Severity::TRACE, "[trace]"},
        {Severity::DEBUG, "[debug]"},
        {Severity::INFO, "[info]"},
        {Severity::WARNING, "[warning]"},
        {Severity::ERROR, "[error]"},
        {Severity::FATAL, "[fatal]"}
    };

    bool individual_logs = false;
    bool working = false;

    int current_log_file = 0;

    DefaultSettings settings {
        "../logs/", // Logs directory
        500, // Max file size (in bytes)
        66, // Max line size
        Time::TIME,
        LoggingPattern::SEV_MSG
    };

private:
    void checkLogsDirectory() {
        // Stablishes the logs directory
        boost::filesystem::path log_directory("../logs");

        // Removes any logs if any exist
        boost::filesystem::remove_all(log_directory);

        // Creates the logs directory if it does not exist
        boost::filesystem::create_directory(log_directory);
    }

    void openLogFile() {
        // Increments the file counter
        current_log_file++;

        file = std::ofstream("../logs/log_file" + std::to_string(current_log_file) + ".txt", std::ios::out);
    }

    std::string getTime() {
        // If the user does not want time, gives nothing
        if (settings.time_representation == Time::NONE) { return ""; }

        // Gets the time
        std::time_t curTime = std::time(nullptr);

        // Gets a better representation of the time
        std::tm *tm = std::localtime(&curTime);

        // Starts the current time with a bracket
        std::string current_time = "[";

        // Inserts time data based on the time representation settings...

        if (settings.time_representation & Time::WEEK) {
            current_time += weeks_map.at(tm->tm_wday);
        }

        if (settings.time_representation & Time::MONTH) {
            // Adds a space between the last time data if any
            if (current_time.size() > 1) { current_time += " "; }

            current_time += months_map.at(tm->tm_mon);
        }

        if (settings.time_representation & Time::DAY) {
            // Adds a space between the last time data if any
            if (current_time.size() > 1) { current_time += " "; }

            int curDay = tm->tm_mday;

            current_time += (curDay < 10 ? "0" + std::to_string(curDay): std::to_string(curDay));
        }

        if (settings.time_representation & Time::YEAR) {
            // Adds a space between the last time data if any
            if (current_time.size() > 1) { current_time += " "; }

            current_time += std::to_string(tm->tm_year + 1900);
        }

        if (settings.time_representation & Time::TIME) {
            // Closes the calendar section and opens one for the time itself, if any data info already written
            if (current_time.size() > 1) { current_time += "]["; }

            int hour_t = tm->tm_hour, min_t = tm->tm_min, sec_t = tm->tm_sec;

            current_time += (hour_t < 10 ? "0" + std::to_string(hour_t): std::to_string(hour_t));
            current_time += ":";
            current_time += (min_t < 10 ? "0" + std::to_string(min_t) : std::to_string(min_t));
            current_time += ":";
            current_time += (sec_t < 10 ? "0" + std::to_string(sec_t) : std::to_string(sec_t));
        }

        // Closes the bracket
        current_time.push_back(']');

        return current_time;
    }

    void writeTime(std::string &log_message) {
        log_message += getTime();
    }
    
    void writeSeverity(std::string &log_message, Severity severity) {
        log_message += severity_levels.at(severity);
    }

    void checkFileSize() {
        // Checks if the current log file has already reached the maximum size
        if (file.tellp() >= settings.max_file_size) {
            // Closes the current log file
            file.close();

            // Opens a new log file
            openLogFile();
        }
    }

    //void startTimer

public:
    Logger() {}
    ~Logger() {
        if(file.is_open()) { file.close(); }
    }

    void init(bool individualLogs = false) {
        checkLogsDirectory();
        openLogFile();
        working = true;
    }

    template<typename T, Settings S>
    void setSettings(T value) {}

    template<typename T>
    void setSettings(Settings setting, T value) {
        switch (setting)
        {
            case Settings::LOG_DIR:
                if( typeid(T) == typeid(settings.logging_pattern)) {
                    settings.logs_directory = (char*)value;
                }
                else { writeLog(Severity::ERROR, "Setting LOG_DIR was given in an incorrect type."); }
                break;
            case Settings::FILE_SIZE:
                if( typeid(T) == typeid(settings.max_file_size)) {
                    settings.max_file_size = (int)value;
                }
                else { writeLog(Severity::ERROR, "Setting FILE_SIZE was given in an incorrect type."); }
                break;
            case Settings::LINE_SIZE:
                if( typeid(T) == typeid(settings.max_line_size)) {
                    settings.max_line_size = (int)value;
                }
                else { writeLog(Severity::ERROR, "Setting LINE_SIZE was given in an incorrect type."); }
                break;
            case Settings::TIME_REP:
                if( typeid(T) == typeid(settings.time_representation)) {
                    settings.time_representation = (Time)value;
                }
                else { writeLog(Severity::ERROR, "Setting TIME_REPRESENTATION was given in an incorrect type."); }
                break;
            case Settings::LOG_PATT:
                if( typeid(T) == typeid(settings.logging_pattern)) {
                    settings.logging_pattern = (LoggingPattern)value;
                }
                else { writeLog(Severity::ERROR, "Setting LOGGING_PATTERN was given in an incorrect type."); }
                break;
            default:
                writeLog(Severity::ERROR, "Setting not recognized.");
                break;
        }
    }

    void setSettings(DefaultSettings settings) {
        this->settings = settings;
    }

    void writeLog(Severity severity, const std::string &message) {
        if (working) {
            std::string log;

            if (settings.logging_pattern == LoggingPattern::TIME_SEV_MSG) {
                writeTime(log);
            }

            writeSeverity(log, severity);

            if (settings.logging_pattern == LoggingPattern::SEV_TIME_MSG) {
                writeTime(log);
            }

            log += " " + message;

            if (settings.logging_pattern == LoggingPattern::SEV_MSG_TIME) {
                log += " ";
                writeTime(log);
            }

            log += '\n';

            file.write (log.c_str(), log.size());

            checkFileSize();
        }
    }

    void writeLog(std::string header) {
        if (working) {
            std::string log_init, log_end;
            for (int i = 0; i < settings.max_line_size; i++) { log_init.push_back('*'); }
            log_end = log_init;

            writeLog(Severity::INFO, log_init);
            TextUtils::Alignment::center(header, settings.max_line_size);
            writeLog(Severity::INFO, header);
            writeLog(Severity::INFO, log_end);
        }
    }
};

void someDummyProcess(Logger &logger) {
    int wait = rand() % 5;
    sleep(wait);
    logger.writeLog(Severity::INFO, "Just a message " + std::to_string(wait) + " seconds later.");
}

int main(int argc, char* argv[])
{
    Logger logger;

    logger.init();

    logger.writeLog(Severity::TRACE, "Testing TRACE log.");
    logger.writeLog(Severity::DEBUG, "Testing DEBUG log.");
    logger.writeLog(Severity::INFO, "Testing INFO log.");
    logger.writeLog(Severity::WARNING, "Testing WARNING log.");
    logger.writeLog(Severity::ERROR, "Testing ERROR log.");
    logger.writeLog(Severity::FATAL, "Testing FATAL log.");

    std::string test;
    for (int i = 0; i < 84; i++) {
        test += std::to_string( i % 2 );
    }

    logger.writeLog(Severity::INFO, test);

    logger.writeLog("This is just a header");
    logger.writeLog(Severity::INFO, "Message after the header.");

    someDummyProcess(logger);

    logger.writeLog(Severity::TRACE, __function__);

    return 0;
}