#pragma once

#include <fstream>
#include <vector>
#include <mutex>
#include <unordered_map>

#include <gabe/logging/SeverityLevel.hpp>
#include <gabe/logging/handlers/Handler.hpp>
#include <gabe/logging/formatters/Formatter.hpp>

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

                std::unordered_map<std::string, formatters::Formatter*> _formatters;

                std::string _message_format = "[%sev] %msg";

                std::mutex _log_mutex;

                std::unordered_map<SeverityLevel, std::string> _formatting = {
                    { SeverityLevel::TRACE,   "TRACE" },
                    { SeverityLevel::DEBUG,   "DEBUG" },
                    { SeverityLevel::INFO,    "INFO" },
                    { SeverityLevel::WARNING, "WARNING" },
                    { SeverityLevel::ERROR,   "ERROR" },
                    { SeverityLevel::FATAL,   "FATAL" }
                };
            
            protected:
                void _open_log_file();
                void _close_log_file();
                void _delete_handlers();
                void _delete_formatters();

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

                template<typename FormatterT>
                void add_formatter(const FormatterT &formatter) {
                    FormatterT* formatter_copy = new FormatterT();
                    *formatter_copy = formatter;

                    if (_formatters.find(formatter.type()) != _formatters.end()) {
                        delete _formatters[formatter.type()];
                    }

                    _formatters[formatter.type()] = dynamic_cast<formatters::Formatter*>(formatter_copy);
                }

                template<typename HandlerT>
                void add_handler(const HandlerT &handler) {
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
