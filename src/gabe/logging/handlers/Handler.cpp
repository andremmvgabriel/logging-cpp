#include <gabe/logging/handlers/Handler.hpp>

std::string gabe::logging::handlers::Handler::type() {
    return _type;
}

bool gabe::logging::handlers::Handler::evaluate() { return false; }

void gabe::logging::handlers::Handler::handle() {}
