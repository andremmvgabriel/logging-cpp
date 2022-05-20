#include <gabe/logging/formatters/Calendar.hpp>

#include <fmt/format.h>

/*
Internal Formatters
*/

gabe::logging::formatters::Calendar::InternalFormatter::InternalFormatter() : Formatter("InternalFormatter", ""), _calendar(nullptr) {}

gabe::logging::formatters::Calendar::InternalFormatter::InternalFormatter(const std::string &type, const std::string &key, std::tm *calendar) : Formatter(type, key), _calendar(calendar) {}



gabe::logging::formatters::Calendar::Year::Year() : InternalFormatter("YearFormatter", "%year", nullptr) {}

gabe::logging::formatters::Calendar::Year::Year(const std::string &key, std::tm *calendar) : InternalFormatter("YearFormatter", key, calendar) {}

std::string gabe::logging::formatters::Calendar::Year::_get_year() {
    return fmt::format("{:04}", _calendar->tm_year + 1900);
}

std::string gabe::logging::formatters::Calendar::Year::_format() {
    if (!_calendar) return "";
    return _get_year();
}



gabe::logging::formatters::Calendar::Month::Month() : InternalFormatter("MonthFormatter", "%smonth", nullptr) {}

gabe::logging::formatters::Calendar::Month::Month(const std::string &key, std::tm *calendar) : InternalFormatter("MonthFormatter", key, calendar) {}

std::string gabe::logging::formatters::Calendar::Month::_get_month() {
    return fmt::format("{:02}", _calendar->tm_mon);
}

std::string gabe::logging::formatters::Calendar::Month::_get_month_str() {
    return _months[_calendar->tm_mon];
}

std::string gabe::logging::formatters::Calendar::Month::_format() {
    if (!_calendar) return "";
    if (_key == "%month") return _get_month();
    else if (_key == "%smonth") return _get_month_str();
    return "";
}



gabe::logging::formatters::Calendar::Day::Day() : InternalFormatter("DayFormatter", "%day", nullptr) {}

gabe::logging::formatters::Calendar::Day::Day(const std::string &key, std::tm *calendar) : InternalFormatter("DayFormatter", key, calendar) {}

std::string gabe::logging::formatters::Calendar::Day::_get_day() {
    return fmt::format("{:02}", _calendar->tm_mday);
}

std::string gabe::logging::formatters::Calendar::Day::_format() {
    if (!_calendar) return "";
    return _get_day();
}



gabe::logging::formatters::Calendar::Week::Week() : InternalFormatter("DayFormatter", "%sweek", nullptr) {}

gabe::logging::formatters::Calendar::Week::Week(const std::string &key, std::tm *calendar) : InternalFormatter("WeekFormatter", key, calendar) {}

std::string gabe::logging::formatters::Calendar::Week::_get_week_day() {
    return fmt::format("{:01}", _calendar->tm_wday + 1);
}

std::string gabe::logging::formatters::Calendar::Week::_get_week_day_str() {
    return _week_days[_calendar->tm_wday];
}

std::string gabe::logging::formatters::Calendar::Week::_format() {
    if (!_calendar) return "";
    if (_key == "%week") return _get_week_day();
    else if (_key == "%sweek") return _get_week_day_str();
    return "";
}



/*
Calendar Formatter
*/

gabe::logging::formatters::Calendar::Calendar() : MultiFormatter("CalendarFormatter") {}

gabe::logging::formatters::Calendar::~Calendar() {
    delete _calendar;
}

void gabe::logging::formatters::Calendar::format(std::string &message) {
    std::time_t epoch = std::time(nullptr);
    localtime_r(&epoch, _calendar);

    _year.format(message);
    _month.format(message);
    _smonth.format(message);
    _day.format(message);
    _week.format(message);
    _sweek.format(message);
}
