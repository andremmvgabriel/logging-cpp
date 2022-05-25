#include <gabe/logging/handlers/TimeRotatingFileHandler.hpp>

#include <fmt/format.h>

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

std::string gabe::logging::handlers::TimeRotatingFileHandler::_find_and_get_before(const std::string &target, const std::string &key, bool last) {
    std::size_t position = last ? target.find_last_of(key) : target.find_first_of(key);

    if (position != -1) return std::string(&target[0], &target[position]);

    return target;
}

std::string gabe::logging::handlers::TimeRotatingFileHandler::_find_and_get_after(const std::string &target, const std::string &key, bool last) {
    std::size_t position = last ? target.find_last_of(key) : target.find_first_of(key);

    if (position != -1) return std::string(&target[position + 1]);

    return target;
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

void gabe::logging::handlers::TimeRotatingFileHandler::_rotate_file(core::Sink *sink) {
    std::string name = _find_and_get_before(sink->file_name(), ".", true);

    std::string year = fmt::format("{:04}", _time_calendar.tm_year + 1900);
    std::string month = fmt::format("{:02}", _time_calendar.tm_mon + 1);
    std::string day = fmt::format("{:02}", _time_calendar.tm_mday);

    std::string hour = fmt::format("{:02}", _time_calendar.tm_hour);
    std::string minutes = fmt::format("{:02}", _time_calendar.tm_min);

    std::string new_name = sink->file_directory() + "/" + name + "_" + year + "-" + month + "-" + day + "_" + hour + "h" + minutes + "m";

    if (sink->file_name().find(".") != -1) new_name += "." + _find_and_get_after(sink->file_name(), ".", true);

    rename(sink->file_full_path().data(), new_name.data());

    // Updates the time
    _time_epoch = std::time(nullptr);
    localtime_r(&_time_epoch, &_time_calendar);
}

void gabe::logging::handlers::TimeRotatingFileHandler::check_sink(core::Sink *sink) {
    struct stat result;

    if(stat(sink->file_full_path().c_str(), &result)==0)
        _time_epoch = result.st_mtime;
        localtime_r(&_time_epoch, &_time_calendar);

        std::time_t time_epoch = std::time(nullptr);
        std::tm time_calendar;
        localtime_r(&time_epoch, &time_calendar);

        // Makes the specified evaluation
        if ((*this.*_evaluation_methods[_rotation])(time_calendar)) {
            sink->flush();
            sink->close_file();
            _rotate_file(sink);
            sink->open_file();
        }
}

void gabe::logging::handlers::TimeRotatingFileHandler::handle(core::Sink *sink, const std::string &message) {
    std::time_t time_epoch = std::time(nullptr);
    std::tm time_calendar;

    localtime_r(&time_epoch, &time_calendar);

    // Checks if the current time somehow went back
    if (time_epoch <= _time_epoch) return;

    // Makes the specified evaluation
    if ((*this.*_evaluation_methods[_rotation])(time_calendar)) {
        sink->flush();
        sink->close_file();
        _rotate_file(sink);
        sink->open_file();
    }
}
