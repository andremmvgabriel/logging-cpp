#include <gabe/logging/formatters/Time.hpp>

#include <ctime>
#include <chrono>
#include <fmt/format.h>

//gabe::logging::formatters::Time::Time() : Formatter::Formatter("TimeFormatter") {}

gabe::logging::formatters::Time::Time(const Layout &layout) : Formatter::Formatter("TimeFormatter", "%time"), _layout(layout) {}

std::string gabe::logging::formatters::Time::_clock() {
    using namespace std::chrono;
    std::time_t epoch = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();

    std::tm calendar;

    localtime_r(&epoch, &calendar);

    return fmt::format("{:02}:{:02}:{:02}", calendar.tm_hour, calendar.tm_min, calendar.tm_sec);
}

std::string gabe::logging::formatters::Time::_clock_ms() {
    using namespace std::chrono;
    
    milliseconds msecs = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    std::time_t epoch = (double)msecs.count() / 1000.0;
    int decimals = ((double)msecs.count() / 1000.0 - epoch) * 1000;

    std::tm calendar;

    localtime_r(&epoch, &calendar);

    return fmt::format("{:02}:{:02}:{:02}.{:03}", calendar.tm_hour, calendar.tm_min, calendar.tm_sec, decimals);
}

std::string gabe::logging::formatters::Time::_epoch() {
    using namespace std::chrono;
    seconds secs = duration_cast<seconds>(system_clock::now().time_since_epoch());

    return fmt::format("{0:d}", secs.count());
}

std::string gabe::logging::formatters::Time::_epoch_ms() {
    using namespace std::chrono;
    milliseconds msecs = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    return fmt::format("{:.3f}", (double)msecs.count() / 1000.0);
}

void gabe::logging::formatters::Time::set_layout(const Time::Layout &layout) {
    _layout = layout;
}

std::string gabe::logging::formatters::Time::_format() {
    return (*this.*_format_methods[_layout])();
}
