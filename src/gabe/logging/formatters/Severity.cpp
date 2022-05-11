#include <gabe/logging/formatters/Severity.hpp>

gabe::logging::formatters::Severity::Severity() : Formatter::Formatter("SeverityFormatter", "%sev") {}

std::string gabe::logging::formatters::Severity::_format() {
    return "";
}