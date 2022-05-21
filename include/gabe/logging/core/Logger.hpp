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
                class Severity : public formatters::Formatter
                {
                protected:
                    std::unordered_map<SeverityLevel, std::string> _formatting = {
                        {   SeverityLevel::TRACE,   "TRACE"     },
                        {   SeverityLevel::DEBUG,   "DEBUG"     },
                        {   SeverityLevel::INFO,    "INFO"      },
                        {   SeverityLevel::WARNING, "WARNING"   },
                        {   SeverityLevel::ERROR,   "ERROR"     },
                        {   SeverityLevel::FATAL,   "FATAL"     }
                    };

                    SeverityLevel _severity;
                
                protected:
                    virtual std::string _format() override;

                public:
                    Severity();

                    void set_severity(const SeverityLevel &severity);
                };

                class Message : public formatters::Formatter
                {
                protected:
                    std::string _message;
                
                protected:
                    virtual std::string _format() override;
                
                public:
                    Message();

                    void set_message(const std::string &message);

                    virtual void format(std::string &message) override;
                };

            protected:
                Sink *_sink = nullptr;

                SeverityLevel _severity = SeverityLevel::INFO;

                std::unordered_map<std::string, handlers::Handler*> _handlers;

                std::unordered_map<std::string, formatters::Formatter*> _formatters;

                std::string _log_layout = "[%sev] %msg";

                std::mutex _log_mutex;
            
            protected:
                void _setup_internal_formatters();
                void _delete_sink();
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

                void set_log_layout(const std::string &log_layout);

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
