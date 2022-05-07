#pragma once

#include <fstream>
#include <unordered_map>

#include <gabe/logging/SeverityLevel.hpp>
#include <gabe/logging/handlers/Handler.hpp>

#include <gabe/logging/core/Sink.hpp>

namespace gabe {
    namespace logging {
        namespace core {
            class Logger
            {
            protected:
                Sink _sink;
                std::ofstream _log_file;

                SeverityLevel _severity = SeverityLevel::INFO;

                std::unordered_map<std::string, handlers::Handler*> _handlers;
            
            protected:
                void _open_log_file();
                void _close_log_file();
                void _delete_handlers();

            public:
                Logger();
                Logger(const SeverityLevel &severity);

                ~Logger();

                void log(const SeverityLevel &severity, const std::string &message);

                void trace(const std::string &message);
                void debug(const std::string &message);
                void info(const std::string &message);
                void warning(const std::string &message);
                void error(const std::string &message);
                void fatal(const std::string &message);

                template<typename HandlerT>
                void add_handler(const HandlerT& handler) {
                    HandlerT* handler_copy = new HandlerT();
                    *handler_copy = handler;
                    
                    if (_handlers.find(handler.type()) != _handlers.end()) {
                        delete _handlers[handler.type()];
                    }

                    _handlers[handler.type()] = dynamic_cast<handlers::Handler*>(handler_copy);
                }
            };
        }
    }
}
