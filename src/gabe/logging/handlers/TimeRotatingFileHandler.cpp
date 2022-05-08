#include <gabe/logging/handlers/TimeRotatingFileHandler.hpp>

#include <fmt/format.h>

gabe::logging::handlers::TimeRotatingFileHandler::TimeRotatingFileHandler() : Handler::Handler("TimeRotatingFile") {}

gabe::logging::handlers::TimeRotatingFileHandler::TimeRotatingFileHandler(const gabe::logging::handlers::TimeRotatingFileHandler::Rotation &rotation) : Handler::Handler("TimeRotatingFile"), _rotation(rotation) {
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

void gabe::logging::handlers::TimeRotatingFileHandler::_rotate_file(const std::string& old_name) {
    std::size_t dot_pos = old_name.find(".");

    std::string name(&old_name.data()[0], &old_name.data()[dot_pos]);
    std::string extension(&old_name.data()[dot_pos]);

    std::string year = fmt::format("{:04}", _time_calendar.tm_year + 1900);
    std::string month = fmt::format("{:02}", _time_calendar.tm_mon + 1);
    std::string day = fmt::format("{:02}", _time_calendar.tm_mday);

    std::string hour = fmt::format("{:02}", _time_calendar.tm_hour);
    std::string minutes = fmt::format("{:02}", _time_calendar.tm_min);

    std::string new_name = name + "_" + year + "-" + month + "-" + day + "_" + hour + "h" + minutes + "m" + extension;

    rename(old_name.data(), new_name.data());
}

bool gabe::logging::handlers::TimeRotatingFileHandler::evaluate() {
    std::time_t time_epoch = std::time(nullptr);
    std::tm time_calendar;
    localtime_r(&time_epoch, &time_calendar);

    // Checks if the current time somehow went back
    if (time_epoch <= _time_epoch) return false;

    // Makes the specified evaluation
    return (*this.*_evaluation_methods[_rotation])(time_calendar);
}

void gabe::logging::handlers::TimeRotatingFileHandler::handle() {
    _time_epoch = std::time(nullptr);
    localtime_r(&_time_epoch, &_time_calendar);

    _rotate_file("logs/log_file.txt");
}
