#include <iostream>
#include <unordered_map>
#include <fstream>

#include <boost/filesystem.hpp>

#include <ctime>

#include <type_traits>

enum class Severity
{
    TRACE   = 1,
    DEBUG   = 2,
    INFO    = 4,
    WARNING = 8,
    ERROR   = 16,
    FATAL   = 32
};

enum class LogginPattern
{
    SEV,
    TIME_SEV,
    SEV_TIME
};

enum Time
{
    NONE    = 0,
    SEC     = 1,
    MIN     = 2,
    HOUR    = 4
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

class Logger
{
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

    Time time = Time::NONE;
    LogginPattern logPattern;

    std::time_t local_time = std::time(nullptr);

    std::string iteration_buffer;

private:
    void checkLogsDirectory() {
        // Stablishes the logs directory
        boost::filesystem::path log_directory("../logs");

        // Creates the logs directory if it does not exist
        boost::filesystem::create_directory(log_directory);
    }

    void addLogFile() {
        file = std::ofstream("../logs/log_file.txt", std::ios::out);
    }

    void writeTime(std::string &log_message) {
        if (time == Time::NONE) { return; }

        std::time_t myTime = std::time(nullptr);

        struct tm* localtime;
        localtime = std::localtime(&myTime);

        int hour_t = localtime->tm_hour;
        int min_t = localtime->tm_min;
        int sec_t = localtime->tm_sec;

        if (time & Time::HOUR) {
            log_message += "[";
            log_message += (hour_t < 10 ? "0" + std::to_string(hour_t): std::to_string(hour_t));
            log_message += ":";
            log_message += (min_t < 10 ? "0" + std::to_string(min_t) : std::to_string(min_t));
            log_message += ":";
            log_message += (sec_t < 10 ? "0" + std::to_string(sec_t) : std::to_string(sec_t));
            log_message += "]";
        }
    }
    
    void writeSeverity(std::string &log_message, Severity severity) {
        log_message += severity_levels.at(severity);
    }

public:
    Logger() {}
    ~Logger() {
        if(file.is_open()) { file.close(); }
    }

    void init(bool individualLogs = false) {
        checkLogsDirectory();
        addLogFile();
        working = true;
        time = Time::HOUR | Time::MIN | Time::SEC;
    }

    void writeLog(Severity severity, std::string message) {
        if (working) {
            std::string log;

            writeTime(log);

            writeSeverity(log, severity);

            log += " " + message + "\n";

            file.write (log.c_str(), log.size());
        }
    }
};


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

    return 0;
}