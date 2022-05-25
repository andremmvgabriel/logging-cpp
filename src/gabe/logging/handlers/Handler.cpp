#include <gabe/logging/handlers/Handler.hpp>

gabe::logging::handlers::Handler::Handler() : _type("DefaultHandler") {}

gabe::logging::handlers::Handler::Handler(const std::string &type) : _type(type) {}

std::string gabe::logging::handlers::Handler::type() const {
    return _type;
}

void gabe::logging::handlers::Handler::check_sink(core::Sink *sink) {}

void gabe::logging::handlers::Handler::handle(core::Sink *sink, const std::string &message) {}
