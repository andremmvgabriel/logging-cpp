#include <gabe/logging/handlers/ConsoleStdOutHandler.hpp>

gabe::logging::handlers::ConsoleStdOutHandler::ConsoleStdOutHandler() : Handler("ConsoleStdOutHandler") {}

void gabe::logging::handlers::ConsoleStdOutHandler::handle(core::Sink *sink, const std::string &message) {
    printf("%s", message.c_str());
}
