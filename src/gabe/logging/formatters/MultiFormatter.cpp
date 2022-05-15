#include <gabe/logging/formatters/MultiFormatter.hpp>

gabe::logging::formatters::MultiFormatter::MultiFormatter() : Formatter(), _layout("") {}

gabe::logging::formatters::MultiFormatter::MultiFormatter(const std::string &type, const std::string &key) : Formatter(type, key), _layout("") {}

gabe::logging::formatters::MultiFormatter::MultiFormatter(const std::string &type, const std::string &key, const std::string &layout) : Formatter(type, key), _layout(layout) {}

std::string gabe::logging::formatters::MultiFormatter::layout() const {
    return _layout;
}
