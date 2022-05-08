#include <gabe/logging/formatters/Time.hpp>

#include <ctime>
#include <chrono>
#include <fmt/format.h>

gabe::logging::formatters::Time::Time() {}
gabe::logging::formatters::Time::Time(const Formatter::Placement &placement, const Layout &layout) : _placement(placement), _layout(layout) {}

std::string gabe::logging::formatters::Time::_clock() {
    using namespace std::chrono;
    std::time_t epoch = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();

    std::tm calendar;

    localtime_r(&epoch, &calendar);

    return fmt::format("[{:02}:{:02}:{:02}]", calendar.tm_hour, calendar.tm_min, calendar.tm_sec);
}

std::string gabe::logging::formatters::Time::_clock_ms() {
    using namespace std::chrono;
    
    milliseconds msecs = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    std::time_t epoch = (double)msecs.count() / 1000.0;
    int decimals = ((double)msecs.count() / 1000.0 - epoch) * 1000;

    std::tm calendar;

    localtime_r(&epoch, &calendar);

    return fmt::format("[{:02}:{:02}:{:02}.{:03}]", calendar.tm_hour, calendar.tm_min, calendar.tm_sec, decimals);
}

std::string gabe::logging::formatters::Time::_epoch() {
    using namespace std::chrono;
    seconds secs = duration_cast<seconds>(system_clock::now().time_since_epoch());

    return fmt::format("[{0:d}]", secs.count());
}

std::string gabe::logging::formatters::Time::_epoch_ms() {
    using namespace std::chrono;
    milliseconds msecs = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    return fmt::format("[{:.3f}]", (double)msecs.count() / 1000.0);
}

void gabe::logging::formatters::Time::set_placement(const gabe::logging::formatters::Formatter::Placement &placement) {
    _placement = placement;
}

void gabe::logging::formatters::Time::set_layout(const gabe::logging::formatters::Time::Layout &layout) {
    _layout = layout;
}

void gabe::logging::formatters::Time::format(std::string &message) {
    if ((uint8_t)_placement > (uint8_t)Formatter::Placement::BEFORE_LOG)
        message = fmt::format("{} {}", message, (*this.*_format_methods[_layout])());
    else
        message = fmt::format("{} {}", (*this.*_format_methods[_layout])(), message);
}
