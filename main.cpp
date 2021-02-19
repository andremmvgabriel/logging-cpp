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
        std::string base_file_name;
        int max_file_size;
        int max_line_size;
        Time time_representation;
        LoggingPattern logging_pattern;
        bool individual_files;
    };

    class LoggerIterator
    {
    
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
    std::unordered_map<Severity, int> current_log_files;

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
        // Increments the file counter
        current_log_file++;

        log_file = std::ofstream(
            settings.logs_directory +
            settings.base_file_name +
            std::to_string(current_log_file) +
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
        // Checks if the current log file has already reached the maximum size
        if (log_file.tellp() >= settings.max_file_size) {
            // Closes the current log file
            log_file.close();

            // Opens a new log file
            openLogFile();
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
        openLogFile();
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

    // For ints / enums
    void setSettings(Settings setting, int value) {
        switch (setting)
        {
            case Settings::FILE_SIZE: settings.max_file_size = value; break;
            case Settings::LINE_SIZE: settings.max_line_size = value; break;
            case Settings::TIME_REP: settings.time_representation = (Time)value; break;
            case Settings::LOG_PATT: settings.logging_pattern = (LoggingPattern)value; break;
            default: writeLog(Severity::WARNING, "Setting not recognized."); break;
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

            log_file.write (log.c_str(), log.size());

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

/*
Haps Simulator

[Article] https://ieeexplore.ieee.org/document/8396531  -> Modelica OOP? "The acausal and object-oriented modeling language Modelica has been used to create the integrated simulation model, enabling a modular and detailed modeling approach."

Será isto?
https://www.simulationx.com/simulation-software/experts/modelica-simulation.html
https://openmodelica.org/uncategorised/191-omsimulator


[Web Site] https://www.atlanticmicrowave.com/application/haps-high-altitude-pseudo-satellite-testing
https://www.atlanticmicrowave.com/news/2021/02/bench-mounted-satellite-simulator-equipment
https://www.atlanticmicrowave.com/markets/satellite-communications

Sao apenas produtos/hardware que se pode comprar para simular?


Drones Simulator -> The best ones are paid, and are not opensource...

[Software] https://www.dji.com/pt/simulator  -> uff

[Software] https://zephyr-sim.com/ -> Zephyr

[GitHub OPENSOURCE!!] https://github.com/microsoft/AirSim -> You would have to understand the code to manage whatever else you want.

Other opensources... But not smelling that good... https://opensource.com/article/18/2/drone-projects


Last resource...
Develop a simulation on Unity / Unreal Engine 4.


*/