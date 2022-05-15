#include <gabe/logging/formatters/Time.hpp>

#include <ctime>
#include <fmt/format.h>

/*
Internal Formatters
*/

gabe::logging::formatters::Time::InternalFormatter::InternalFormatter() : Formatter("InternalFormatter", ""), _time_ms(nullptr) {}

gabe::logging::formatters::Time::InternalFormatter::InternalFormatter(const std::string &type, const std::string &key, std::chrono::milliseconds *time_ms) : Formatter(type, key), _time_ms(time_ms) {}



gabe::logging::formatters::Time::Clock::Clock() : InternalFormatter("ClockFormatter", "%clock", nullptr) {}

gabe::logging::formatters::Time::Clock::Clock(const std::string &key, std::chrono::milliseconds *time_ms) : InternalFormatter("ClockFormatter", key, time_ms) {}

std::string gabe::logging::formatters::Time::Clock::_get_clock() {
    std::time_t epoch = (double)_time_ms->count() / 1000.0;

    std::tm calendar;
    localtime_r(&epoch, &calendar);

    return fmt::format("{:02}:{:02}:{:02}", calendar.tm_hour, calendar.tm_min, calendar.tm_sec);
}

std::string gabe::logging::formatters::Time::Clock::_get_clock_ms() {
    double seconds = (double)_time_ms->count() / 1000.0;
    std::time_t epoch = seconds;
    int decimals = (seconds - epoch) * 1000;

    std::tm calendar;
    localtime_r(&epoch, &calendar);

    return fmt::format("{:02}:{:02}:{:02}.{:03}", calendar.tm_hour, calendar.tm_min, calendar.tm_sec, decimals);
}

std::string gabe::logging::formatters::Time::Clock::_format() {
    if (!_time_ms) return "";
    if (_key == "%clock") return _get_clock();
    else if (_key == "%msclock") return _get_clock_ms();
    return "";
}



gabe::logging::formatters::Time::Epoch::Epoch() : InternalFormatter("EpochFormatter", "", nullptr) {}

gabe::logging::formatters::Time::Epoch::Epoch(const std::string &key, std::chrono::milliseconds *time_ms) : InternalFormatter("EpochFormatter", key, time_ms) {}

std::string gabe::logging::formatters::Time::Epoch::_get_epoch() {
    int seconds = (double)_time_ms->count() / 1000.0;

    return fmt::format("{0:d}", seconds);
}

std::string gabe::logging::formatters::Time::Epoch::_get_epoch_ms() {
    return fmt::format("{:.3f}", (double)_time_ms->count() / 1000.0);
}

std::string gabe::logging::formatters::Time::Epoch::_format() {
    if (!_time_ms) return "";
    if (_key == "%epoch") return _get_epoch();
    else if (_key == "%msepoch") return _get_epoch_ms();
    return "";
}



/*
Time Formatter
*/

gabe::logging::formatters::Time::Time() : MultiFormatter("TimeFormatter", "%time", "%clock_ms") {}

gabe::logging::formatters::Time::Time(const std::string &layout) : MultiFormatter("TimeFormatter", "%time", layout) {}

gabe::logging::formatters::Time::~Time() {
    delete _time_ms;
}

std::string gabe::logging::formatters::Time::_format() {
    *_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    std::string time_str = _layout;

    _clock.format(time_str);
    _clock_ms.format(time_str);
    _epoch.format(time_str);
    _epoch_ms.format(time_str);

    return time_str;
}
