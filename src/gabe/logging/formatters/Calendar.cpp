#include <gabe/logging/formatters/Calendar.hpp>

#include <fmt/format.h>

//gabe::logging::formatters::Calendar::Calendar() : Formatter::Formatter("CalendarFormatter") {}

gabe::logging::formatters::Calendar::Calendar(const std::vector<Layout> &layout) : Formatter::Formatter("CalendarFormatter", "%cal"), _layout(layout) {}

std::string gabe::logging::formatters::Calendar::_get_year(const std::tm &calendar) {
    return fmt::format("{:04}", calendar.tm_year + 1900);
}

std::string gabe::logging::formatters::Calendar::_get_month(const std::tm &calendar) {
    return _months[calendar.tm_mon];
}

std::string gabe::logging::formatters::Calendar::_get_day(const std::tm &calendar) {
    return fmt::format("{:02}", calendar.tm_mday);
}

std::string gabe::logging::formatters::Calendar::_get_weekday(const std::tm &calendar) {
    return _week_days[calendar.tm_wday];
}

std::string gabe::logging::formatters::Calendar::_format() {
    std::time_t epoch = std::time(nullptr);
    std::tm calendar;
    localtime_r(&epoch, &calendar);

    std::string calendar_str = "";

    uint8_t counter = 1;
    for (auto layout : _layout) {
        calendar_str = fmt::format("{}{}", calendar_str, (*this.*_format_methods[layout])(calendar));
        calendar_str += counter == _layout.size() ? "" : " ";
        counter += 1;
    }

    return fmt::format("[{}]", calendar_str);
}

void gabe::logging::formatters::Calendar::set_layout(const std::vector<Layout> &layout) {
    _layout = layout;
}
