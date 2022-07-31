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
    // Converts epoch in milliseconds to seconds.
    std::time_t epoch = (double)_time_ms->count() / 1000.0;

    // Creates a calendar data structure that is filled from the previous epoch
    std::tm calendar;
    localtime_r(&epoch, &calendar);

    // Formats
    return fmt::format("{:02}", calendar.tm_hour);
}

std::string gabe::logging::formatters::Time::Hours::_format() {
    // Safety check
    if (!_time_ms) return "";

    return _get_hours();
}



gabe::logging::formatters::Time::Minutes::Minutes() : InternalFormatter("MinutesFormatter", "%min", nullptr) {}

gabe::logging::formatters::Time::Minutes::Minutes(const std::string &key, std::chrono::milliseconds *time_ms) : InternalFormatter("MinutesFormatter", key, time_ms) {}

std::string gabe::logging::formatters::Time::Minutes::_get_minutes() {
    // Converts epoch in milliseconds to seconds.
    std::time_t epoch = (double)_time_ms->count() / 1000.0;

    // Creates a calendar data structure that is filled from the previous epoch
    std::tm calendar;
    localtime_r(&epoch, &calendar);

    // Formats
    return fmt::format("{:02}", calendar.tm_min);
}

std::string gabe::logging::formatters::Time::Minutes::_format() {
    // Safety check
    if (!_time_ms) return "";

    return _get_minutes();
}



gabe::logging::formatters::Time::Seconds::Seconds() : InternalFormatter("SecondsFormatter", "%sec", nullptr) {}

gabe::logging::formatters::Time::Seconds::Seconds(const std::string &key, std::chrono::milliseconds *time_ms) : InternalFormatter("SecondsFormatter", key, time_ms) {}

std::string gabe::logging::formatters::Time::Seconds::_get_seconds() {
    // Converts epoch in milliseconds to seconds.
    std::time_t epoch = (double)_time_ms->count() / 1000.0;

    // Creates a calendar data structure that is filled from the previous epoch
    std::tm calendar;
    localtime_r(&epoch, &calendar);

    // Formats
    return fmt::format("{:02}", calendar.tm_sec);
}

std::string gabe::logging::formatters::Time::Seconds::_format() {
    // Safety check
    if (!_time_ms) return "";

    return _get_seconds();
}



gabe::logging::formatters::Time::Milliseconds::Milliseconds() : InternalFormatter("MillisecondsFormatter", "%ms", nullptr) {}

gabe::logging::formatters::Time::Milliseconds::Milliseconds(const std::string &key, std::chrono::milliseconds *time_ms) : InternalFormatter("MillisecondsFormatter", key, time_ms) {}

std::string gabe::logging::formatters::Time::Milliseconds::_get_milliseconds() {
    // Converts epoch in milliseconds to seconds.
    double seconds = (double)_time_ms->count() / 1000.0;
    std::time_t epoch = seconds;

    // Calculates the 3 decimal digits
    int decimals = (seconds - epoch) * 1000;

    // Format
    return fmt::format("{:03}", decimals);
}

std::string gabe::logging::formatters::Time::Milliseconds::_format() {
    // Safety check
    if (!_time_ms) return "";

    return _get_milliseconds();
}



gabe::logging::formatters::Time::Epoch::Epoch() : InternalFormatter("EpochFormatter", "%epoch", nullptr) {}

gabe::logging::formatters::Time::Epoch::Epoch(const std::string &key, std::chrono::milliseconds *time_ms) : InternalFormatter("EpochFormatter", key, time_ms) {}

std::string gabe::logging::formatters::Time::Epoch::_get_epoch() {
    // Converts epoch in milliseconds to seconds.
    int seconds = (double)_time_ms->count() / 1000.0;

    // Formats
    return fmt::format("{0:d}", seconds);
}

std::string gabe::logging::formatters::Time::Epoch::_format() {
    // Safety check
    if (!_time_ms) return "";

    return _get_epoch();
}



/*
Time Formatter
*/

gabe::logging::formatters::Time::Time() : MultiFormatter("TimeFormatter") {
    // Creates all the needed internal formatters
    add_formatter( Hours("%hour", _time_ms) );
    add_formatter( Minutes("%min", _time_ms) );
    add_formatter( Seconds("%sec", _time_ms) );
    add_formatter( Milliseconds("%ms", _time_ms) );
    add_formatter( Epoch("%epoch", _time_ms) );
}

gabe::logging::formatters::Time::~Time() {
    delete _time_ms;
}

void gabe::logging::formatters::Time::format(std::string &message) {
    using namespace std::chrono;

    // Updates the time data in epoch milliseconds
    *_time_ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    // Proceeds to the log formatting
    MultiFormatter::format(message);
}
