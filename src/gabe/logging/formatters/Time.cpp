#include <gabe/logging/formatters/Time.hpp>

#include <ctime>
#include <fmt/format.h>

/*
Internal Formatters
*/

gabe::logging::formatters::Time::InternalFormatter::InternalFormatter() : Formatter("InternalFormatter", ""), _time_ms(nullptr) {}

gabe::logging::formatters::Time::InternalFormatter::InternalFormatter(const std::string &type, const std::string &key, std::chrono::milliseconds *time_ms) : Formatter(type, key), _time_ms(time_ms) {}



gabe::logging::formatters::Time::Hours::Hours() : InternalFormatter("HoursFormatter", "%hour", nullptr) {}

gabe::logging::formatters::Time::Hours::Hours(const std::string &key, std::chrono::milliseconds *time_ms) : InternalFormatter("HoursFormatter", key, time_ms) {}

std::string gabe::logging::formatters::Time::Hours::_get_hours() {
    std::time_t epoch = (double)_time_ms->count() / 1000.0;

    std::tm calendar;
    localtime_r(&epoch, &calendar);

    return fmt::format("{:02}", calendar.tm_hour);
}

std::string gabe::logging::formatters::Time::Hours::_format() {
    if (!_time_ms) return "";
    return _get_hours();
}



gabe::logging::formatters::Time::Minutes::Minutes() : InternalFormatter("MinutesFormatter", "%min", nullptr) {}

gabe::logging::formatters::Time::Minutes::Minutes(const std::string &key, std::chrono::milliseconds *time_ms) : InternalFormatter("MinutesFormatter", key, time_ms) {}

std::string gabe::logging::formatters::Time::Minutes::_get_minutes() {
    std::time_t epoch = (double)_time_ms->count() / 1000.0;

    std::tm calendar;
    localtime_r(&epoch, &calendar);

    return fmt::format("{:02}", calendar.tm_min);
}

std::string gabe::logging::formatters::Time::Minutes::_format() {
    if (!_time_ms) return "";
    return _get_minutes();
}



gabe::logging::formatters::Time::Seconds::Seconds() : InternalFormatter("SecondsFormatter", "%sec", nullptr) {}

gabe::logging::formatters::Time::Seconds::Seconds(const std::string &key, std::chrono::milliseconds *time_ms) : InternalFormatter("SecondsFormatter", key, time_ms) {}

std::string gabe::logging::formatters::Time::Seconds::_get_seconds() {
    std::time_t epoch = (double)_time_ms->count() / 1000.0;

    std::tm calendar;
    localtime_r(&epoch, &calendar);

    return fmt::format("{:02}", calendar.tm_sec);
}

std::string gabe::logging::formatters::Time::Seconds::_format() {
    if (!_time_ms) return "";
    return _get_seconds();
}



gabe::logging::formatters::Time::Milliseconds::Milliseconds() : InternalFormatter("MillisecondsFormatter", "%ms", nullptr) {}

gabe::logging::formatters::Time::Milliseconds::Milliseconds(const std::string &key, std::chrono::milliseconds *time_ms) : InternalFormatter("MillisecondsFormatter", key, time_ms) {}

std::string gabe::logging::formatters::Time::Milliseconds::_get_milliseconds() {
    double seconds = (double)_time_ms->count() / 1000.0;
    std::time_t epoch = seconds;
    int decimals = (seconds - epoch) * 1000;

    return fmt::format("{:03}", decimals);
}

std::string gabe::logging::formatters::Time::Milliseconds::_format() {
    if (!_time_ms) return "";
    return _get_milliseconds();
}



gabe::logging::formatters::Time::Epoch::Epoch() : InternalFormatter("EpochFormatter", "%epoch", nullptr) {}

gabe::logging::formatters::Time::Epoch::Epoch(const std::string &key, std::chrono::milliseconds *time_ms) : InternalFormatter("EpochFormatter", key, time_ms) {}

std::string gabe::logging::formatters::Time::Epoch::_get_epoch() {
    int seconds = (double)_time_ms->count() / 1000.0;

    return fmt::format("{0:d}", seconds);
}

std::string gabe::logging::formatters::Time::Epoch::_format() {
    if (!_time_ms) return "";
    return _get_epoch();
}



/*
Time Formatter
*/

gabe::logging::formatters::Time::Time() : MultiFormatter("TimeFormatter") {}

gabe::logging::formatters::Time::~Time() {
    delete _time_ms;
}

void gabe::logging::formatters::Time::format(std::string &message) {
    *_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    _hours.format(message);
    _minutes.format(message);
    _seconds.format(message);
    _milliseconds.format(message);
    _epoch.format(message);
}
