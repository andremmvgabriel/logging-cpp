#include <gabe/logging/formatters/MultiFormatter.hpp>

gabe::logging::formatters::MultiFormatter::MultiFormatter() : Formatter() {}

gabe::logging::formatters::MultiFormatter::MultiFormatter(const std::string &type) : Formatter(type, "") {}

gabe::logging::formatters::MultiFormatter::~MultiFormatter() {
    for (auto formatter : _formatters) {
        delete formatter;
    }
}

void gabe::logging::formatters::MultiFormatter::format(std::string &message) {
    for (auto formatter : _formatters) {
        formatter->format(message);
    }
}
