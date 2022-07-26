#pragma once

#include <fstream>
#include <vector>
#include <mutex>
#include <unordered_map>

#include <fmt/format.h>

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
                Logger *_parent = nullptr;

                SeverityLevel _severity = SeverityLevel::INFO;

                std::unordered_map<std::string, handlers::Handler*> _handlers;

                std::unordered_map<std::string, formatters::Formatter*> _formatters;

                std::string _log_layout = "[%sev] %msg";
                bool _chained_logs = true;

                std::mutex _log_mutex;
            
            protected:
                std::string _filter_logger_name(std::string name);

                void _setup_internal_formatters();
                void _delete_sink();
                void _delete_handlers();
                void _delete_formatters();

                void _log(const SeverityLevel &severity, const std::string &message);

                void _process_handlers(const std::string &message);

            public:
                Logger();
                Logger(const std::string &location, const std::string &name, Logger *parent);
                Logger(const std::string &location, const std::string &name, const SeverityLevel &severity);
                Logger(const std::string &location, const std::string &name, const SeverityLevel &severity, Logger *parent);

                ~Logger();

                template<typename ... Args>
                void log(const SeverityLevel &severity, const std::string &message, Args... args) {
                    std::string formatted_message = fmt::format(message, args...);
                    _log(severity, formatted_message);
                }

                template<typename ... Args>
                void trace(const std::string &message, Args... args) {
                    log(SeverityLevel::TRACE, message, args...);
                }

                template<typename ... Args>
                void debug(const std::string &message, Args... args) {
                    log(SeverityLevel::DEBUG, message, args...);
                }

                template<typename ... Args>
                void info(const std::string &message, Args... args) {
                    log(SeverityLevel::INFO, message, args...);
                }

                template<typename ... Args>
                void warning(const std::string &message, Args... args) {
                    log(SeverityLevel::WARNING, message, args...);
                }

                template<typename ... Args>
                void error(const std::string &message, Args... args) {
                    log(SeverityLevel::ERROR, message, args...);
                }

                template<typename ... Args>
                void fatal(const std::string &message, Args... args) {
                    log(SeverityLevel::FATAL, message, args...);
                }

                void set_log_layout(const std::string &log_layout);
                std::string get_log_layout();

                void set_chained_logs(bool active);
                bool get_chained_logs();

                void set_severity(const SeverityLevel &severity);
                SeverityLevel get_severity();

                void set_logs_location(const std::string &location);
                std::string get_logs_location();

                void set_logs_file_name(const std::string &file_name);
                std::string get_logs_file_name();

                void basic_config(const SeverityLevel &severity, const std::string &location, const std::string &file_name);

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

                    handler_copy->check_sink(_sink);
                    
                    if (_handlers.find(handler.type()) != _handlers.end()) {
                        delete _handlers[handler.type()];
                    }

                    _handlers[handler.type()] = dynamic_cast<handlers::Handler*>(handler_copy);
                }
            };
        }
    }
}
