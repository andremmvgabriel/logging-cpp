#include <gabe/logging/handlers/TimeRotatingFileHandler.hpp>

#include <fmt/format.h>
#include <filesystem>

#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
#include <unistd.h>
#elif
#define stat _stat
#endif

gabe::logging::handlers::TimeRotatingFileHandler::TimeRotatingFileHandler() : Handler("TimeRotatingFile"), _rotation("D") {}

gabe::logging::handlers::TimeRotatingFileHandler::TimeRotatingFileHandler(const std::string &rotation) : Handler("TimeRotatingFile"), _rotation(rotation) {
    _time_epoch = std::time(nullptr);
    localtime_r(&_time_epoch, &_time_calendar);
}

bool gabe::logging::handlers::TimeRotatingFileHandler::_minute_evaluation(const std::tm &time_calendar) {
    if (_time_calendar.tm_min != time_calendar.tm_min) return true;
    else return false;
}

bool gabe::logging::handlers::TimeRotatingFileHandler::_hour_evaluation(const std::tm &time_calendar) {
    if (_time_calendar.tm_hour != time_calendar.tm_hour) return true;
    else return false;
}

bool gabe::logging::handlers::TimeRotatingFileHandler::_day_evaluation(const std::tm &time_calendar) {
    if (_time_calendar.tm_mday != time_calendar.tm_mday) return true;
    else return false;
}

bool gabe::logging::handlers::TimeRotatingFileHandler::_week_evaluation(const std::tm &time_calendar) {
    if (_time_calendar.tm_wday != time_calendar.tm_mday) return true;
    else return false;
}

bool gabe::logging::handlers::TimeRotatingFileHandler::_month_evaluation(const std::tm &time_calendar) {
    if (_time_calendar.tm_mon != time_calendar.tm_mon) return true;
    else return false;
}

void gabe::logging::handlers::TimeRotatingFileHandler::check_sink(core::Sink *sink) {
    // Structure needed to get the time of the last modification of the file
    struct stat result;

    // Updates the time epoch with the last file modification date, otherwise gets the current date
    if(stat(sink->get_file_full_path().c_str(), &result)==0) {
        _time_epoch = result.st_mtime;
    } else {
        _time_epoch = std::time(nullptr);
    }

    // Updates the calendar data structure
    localtime_r(&_time_epoch, &_time_calendar);
}

bool gabe::logging::handlers::TimeRotatingFileHandler::evaluate(core::Sink *sink, const std::string &message) {
    // Gets the current time and gets the calendar data structure from it
    std::time_t time_epoch = std::time(nullptr);
    std::tm time_calendar;
    localtime_r(&time_epoch, &time_calendar);

    // Checks if the current time somehow went back
    if (time_epoch <= _time_epoch) return false;

    // Makes the specified evaluation
    if ((*this.*_evaluation_methods[_rotation])(time_calendar))
        return true;

    return false;
}

std::string gabe::logging::handlers::TimeRotatingFileHandler::create_handled_file_name(const std::string &file_name) {
    // Gets the time as a filesystem path variable
    std::filesystem::path name(file_name);

    // Separates the filename of its extension
    std::string pre_name = name.stem();
    std::string pos_name = name.extension();

    // Finds the last "." so the handler puts the date after the actual logfile name
    std::size_t position = pre_name.find(".");
    while(position != -1) {
        // Removes other handler substring
        pre_name = std::filesystem::path(pre_name).stem();

        // Adds the other handler substring to the pos name
        pos_name = std::string(std::filesystem::path(pos_name).extension()) + pos_name;

        // Keeps trying to find more "."s
        position = pre_name.find(".");
    }

    // Gets all the needed time variables
    std::string year = fmt::format("{:04}", _time_calendar.tm_year + 1900);
    std::string month = fmt::format("{:02}", _time_calendar.tm_mon + 1);
    std::string day = fmt::format("{:02}", _time_calendar.tm_mday);
    std::string hour = fmt::format("{:02}", _time_calendar.tm_hour);
    std::string minutes = fmt::format("{:02}", _time_calendar.tm_min);

    // Creates the new name
    std::string new_name = pre_name + "." + year + "-" + month + "-" + day + "_" + hour + "h" + minutes + pos_name;

    // Updates the time
    _time_epoch = std::time(nullptr);
    localtime_r(&_time_epoch, &_time_calendar);

    return new_name;
}
