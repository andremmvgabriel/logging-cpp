#include <gabe/logging/formatters/Formatter.hpp>

gabe::logging::formatters::Formatter::Formatter() : _type("DefaultFormatter") {}

gabe::logging::formatters::Formatter::Formatter(const std::string &type) : _type(type) {}

gabe::logging::formatters::Formatter::Formatter(const std::string &type, const gabe::logging::formatters::Formatter::Placement &placement) : _type(type), _placement(placement) {}

std::string gabe::logging::formatters::Formatter::type() const {
    return _type;
}

void gabe::logging::formatters::Formatter::set_placement(const gabe::logging::formatters::Formatter::Placement &placement) {
    _placement = placement;
}

gabe::logging::formatters::Formatter::Placement gabe::logging::formatters::Formatter::get_placement() const {
    return _placement;
}

void gabe::logging::formatters::Formatter::format(std::string &message) {}
