#include <gabe/logging/formatters/Calendar.hpp>

#include <ctime>

void gabe::logging::formatters::Calendar::format(std::string &message) {
    std::time_t time_epoch = std::time(nullptr);
    std::tm time_calendar;
    localtime_r(&time_epoch, &time_calendar);
}
