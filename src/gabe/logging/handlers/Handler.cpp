#include <gabe/logging/handlers/Handler.hpp>

gabe::logging::handlers::Handler::Handler() : _type("DefaultHandler") {}

gabe::logging::handlers::Handler::Handler(const std::string &type) : _type(type) {}

std::string gabe::logging::handlers::Handler::type() const {
    return _type;
}

void gabe::logging::handlers::Handler::check_sink(core::Sink *sink) {}

bool gabe::logging::handlers::Handler::evaluate(core::Sink *sink, const std::string &message) { return false; }

std::string gabe::logging::handlers::Handler::create_handled_file_name(const std::string &file_name) { return file_name; }
