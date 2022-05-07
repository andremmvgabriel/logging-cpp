#include <gabe/logging/handlers/TimeRotatingFileHandler.hpp>

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
