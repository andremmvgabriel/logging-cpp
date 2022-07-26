#include <gabe/logging/handlers/ConsoleStdOutHandler.hpp>

gabe::logging::handlers::ConsoleStdOutHandler::ConsoleStdOutHandler() : Handler("ConsoleStdOutHandler") {}

bool gabe::logging::handlers::ConsoleStdOutHandler::evaluate(core::Sink *sink, const std::string &message) {
    printf("%s", message.c_str());
    return false;
}
