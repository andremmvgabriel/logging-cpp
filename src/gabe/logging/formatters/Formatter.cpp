#include <gabe/logging/formatters/Formatter.hpp>

gabe::logging::formatters::Formatter::Formatter() : _type("DefaultFormatter"), _key("") {}

gabe::logging::formatters::Formatter::Formatter(const std::string &type) : _type(type), _key("") {}

gabe::logging::formatters::Formatter::Formatter(const std::string &type, const std::string &key) : _type(type), _key(key) {}

std::string gabe::logging::formatters::Formatter::_format() { return ""; }

std::string gabe::logging::formatters::Formatter::type() const {
    return _type;
}

std::string gabe::logging::formatters::Formatter::key() const {
    return _key;
}

void gabe::logging::formatters::Formatter::format(std::string &message) {
    // Searches the position where the formatting key is located.
    std::size_t key_pos = message.find(_key);

    // Safety check in case the key isn't in the log layout.
    if (key_pos == -1) return;
    
    // Formatting
    message = std::string(&message[0], &message[key_pos]) + _format() + std::string(&message[key_pos + _key.size()]);
}
