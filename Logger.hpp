#pragma once

#include <iostream>
#include <unordered_map>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/current_function.hpp>

#include <ctime>
#include <chrono>

#include <type_traits>

#include "TextUtils.hpp"

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

class Logger
{
private:
    struct DefaultSettings
    {
        std::string logs_directory;
        std::string base_file_name;
        int max_file_size;
        int max_line_size;
        Time time_representation;
        LoggingPattern logging_pattern;
        bool individual_files;
    };

    class LoggerIterator
    {
    private:
        std::vector<std::string> ite_strings;
        std::time_t last_time;
        std::chrono::milliseconds initial_time;
        std::vector<LoggerIterator> chained_iterators;

    public:
        LoggerIterator() {
            // Registers the initial time
            initial_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        }

        void writeIterationLog(const std::string);
        
        std::vector<std::string> getLog() { return ite_strings; }
    };

public:
    enum class Settings
    {
        LOG_DIR,
        FILE_NAME,
        FILE_SIZE,
        LINE_SIZE,
        TIME_REP,
        LOG_PATT,
        IND_FILES
    };

private:
    std::ofstream log_file;
    int current_log_file = 0;

    std::unordered_map<Severity, std::ofstream> log_files;

    std::unordered_map<Severity, int> current_log_files {
        {Severity::TRACE, 0},
        {Severity::DEBUG, 0},
        {Severity::INFO, 0},
        {Severity::WARNING, 0},
        {Severity::ERROR, 0},
        {Severity::FATAL, 0}
    };

    std::unordered_map<Severity, std::string> severity_levels {
        {Severity::TRACE, "[trace]"},
        {Severity::DEBUG, "[debug]"},
        {Severity::INFO, "[info]"},
        {Severity::WARNING, "[warning]"},
        {Severity::ERROR, "[error]"},
        {Severity::FATAL, "[fatal]"}
    };

    bool working = false;

    DefaultSettings settings {
        "../logs/", // Logs directory
        "log_file", // Logs base file name
        500, // Max file size (in bytes)
        66, // Max line size
        Time::TIME,
        LoggingPattern::SEV_MSG,
        false // One log for all severities
    };

private:
    void checkLogsDirectory() {
        // Stablishes the logs directory
        boost::filesystem::path log_directory(settings.logs_directory);

        // Removes any logs if any exist
        boost::filesystem::remove_all(log_directory);

        // Creates the logs directory if it does not exist
        boost::filesystem::create_directory(log_directory);
    }

    void openLogFile() {
        // Closes the previous log file, if opened
        if (log_file.is_open()) { log_file.close(); }

        // Increments the file counter
        current_log_file++;

        // Opens the file
        log_file = std::ofstream(
            settings.logs_directory +
            settings.base_file_name +
            std::to_string(current_log_file) +
            ".txt", std::ios::out
        );
    }

    void openLogFile(Severity severity) {
        // Closes the previous log file, if opened
        if (log_files[severity].is_open()) { log_files.at(severity).close(); }

        // Increments the file counter
        current_log_files.at(severity)++;

        // Opens the file
        log_files.at(severity) = std::ofstream(
            settings.logs_directory +
            settings.base_file_name +
            "_" +
            severity_levels.at(severity) +
            "_" +
            std::to_string( current_log_files.at(severity) ) +
            ".txt", std::ios::out
        );
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
        // Checks if there are files for individual severities or not
        if (settings.individual_files) {
            if (log_files.at(Severity::TRACE).tellp() >= settings.max_file_size)
                openLogFile(Severity::TRACE);
            if (log_files.at(Severity::DEBUG).tellp() >= settings.max_file_size)
                openLogFile(Severity::DEBUG);
            if (log_files.at(Severity::INFO).tellp() >= settings.max_file_size)
                openLogFile(Severity::INFO);
            if (log_files.at(Severity::WARNING).tellp() >= settings.max_file_size)
                openLogFile(Severity::WARNING);
            if (log_files.at(Severity::ERROR).tellp() >= settings.max_file_size)
                openLogFile(Severity::ERROR);
            if (log_files.at(Severity::FATAL).tellp() >= settings.max_file_size)
                openLogFile(Severity::FATAL);
        }
        else {
            // Checks if the current log file has already reached the maximum size
            if (log_file.tellp() >= settings.max_file_size) {
                // Opens a new log file
                openLogFile();
            }
        }
    }

    //void startTimer

public:
    Logger() {}
    ~Logger() {
        if(log_file.is_open()) { log_file.close(); }
    }

    void init(bool individualLogs = false) {
        checkLogsDirectory();

        if (settings.individual_files) {
            openLogFile(Severity::TRACE);
            openLogFile(Severity::DEBUG);
            openLogFile(Severity::INFO);
            openLogFile(Severity::WARNING);
            openLogFile(Severity::ERROR);
            openLogFile(Severity::FATAL);
        }
        else {
            openLogFile();
        }
        
        working = true;
    }

    // For strings
    void setSettings(Settings setting, std::string value) {
        switch (setting)
        {
            case Settings::LOG_DIR: settings.logs_directory = value; break;
            case Settings::FILE_NAME: settings.base_file_name = value; break;
        }
    }

    // For ints / bools / enums
    void setSettings(Settings setting, int value) {
        switch (setting)
        {
            case Settings::FILE_SIZE: settings.max_file_size = value; break;
            case Settings::LINE_SIZE: settings.max_line_size = value; break;
            case Settings::TIME_REP: settings.time_representation = (Time)value; break;
            case Settings::LOG_PATT: settings.logging_pattern = (LoggingPattern)value; break;
            case Settings::IND_FILES: settings.individual_files = (bool)value; break;
            default: writeLog(Severity::WARNING, "Setting not recognized."); break;
        }
    }

    void setSettings(DefaultSettings settings) {
        this->settings = settings;
    }

    void writeLog(Severity severity, const std::string &message) {
        if (working) {
            std::string log;
            std::string timeStr;

            if (settings.logging_pattern == LoggingPattern::TIME_SEV_MSG) {
                log += getTime();
            }

            log += severity_levels.at(severity);

            if (settings.logging_pattern == LoggingPattern::SEV_TIME_MSG) {
                log += getTime();
            }

            if (settings.logging_pattern == LoggingPattern::SEV_MSG_TIME) {
                timeStr = " " + getTime();
            }

            std::string wholeMsg = message;

            bool alive = true;
            while (alive) {
                std::string curLog;
                curLog += log + " ";

                if (wholeMsg.size() > settings.max_line_size) {
                    curLog.insert(curLog.end(), wholeMsg.begin(), wholeMsg.begin() + settings.max_line_size);

                    wholeMsg.erase(wholeMsg.begin(), wholeMsg.begin() + settings.max_line_size);            
                }
                else {
                    curLog += wholeMsg;
                    alive = false;
                }

                curLog += timeStr;
                curLog += '\n';

                if (settings.individual_files) {
                    log_files.at(severity).write(curLog.c_str(), curLog.size());
                }
                else {
                    log_file.write (curLog.c_str(), curLog.size());
                }      

                checkFileSize();               
            }     
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

    //std::unordered_map<>;

    void beginIterationLog(const std::string &message) {

    }

    void endIterationLog() {

    }
};