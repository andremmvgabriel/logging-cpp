#include <gabe/logging/formatters/MultiFormatter.hpp>

gabe::logging::formatters::MultiFormatter::MultiFormatter() : Formatter() {}

gabe::logging::formatters::MultiFormatter::MultiFormatter(const std::string &type) : Formatter(type, "") {}
