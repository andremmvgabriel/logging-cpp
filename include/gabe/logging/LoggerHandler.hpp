#pragma once

#include <gabe/logging/core/Logger.hpp>

namespace gabe {
    namespace logging {
        class LoggerHandler
        {
        public:
            core::Logger *_logger = nullptr;
        
        public:
            LoggerHandler();
            LoggerHandler(core::Logger *logger);

            LoggerHandler(const LoggerHandler &logger_handler);

            LoggerHandler& operator=(const LoggerHandler &logger_handler);

            core::Logger* ptr();

            void set_logs_file_name(const std::string &file_name);
            std::string get_logs_file_name();

            void set_chained_logs(bool active);
            bool get_chained_logs();

            void set_severity(const SeverityLevel &severity);
            SeverityLevel get_severity();

            void set_logs_location(const std::string &location);
            std::string get_logs_location();

            void set_log_layout(const std::string &log_layout);
            std::string get_log_layout();

            void basic_config(const SeverityLevel &severity, const std::string &location, const std::string &file_name);

            template<typename FormatterT>
            void add_formatter(const FormatterT &formatter) {
                _logger->add_formatter(formatter);
            }

            template<typename HandlerT>
            void add_handler(const HandlerT& handler) {
                _logger->add_handler(handler);
            }

            template<typename ... Args>
            void log(const gabe::logging::SeverityLevel &severity, const std::string &message, Args... args) {
                _logger->log(severity, message, args...);
            }

            template<typename ... Args>
            void trace(const std::string &message, Args... args) {
                _logger->trace(message, args...);
            }

            template<typename ... Args>
            void debug(const std::string &message, Args... args) {
                _logger->debug(message, args...);
            }

            template<typename ... Args>
            void info(const std::string &message, Args... args) {
                _logger->info(message, args...);
            }

            template<typename ... Args>
            void warning(const std::string &message, Args... args) {
                _logger->warning(message, args...);
            }

            template<typename ... Args>
            void error(const std::string &message, Args... args) {
                _logger->error(message, args...);
            }

            template<typename ... Args>
            void fatal(const std::string &message, Args... args) {
                _logger->fatal(message, args...);
            }
        };
    }
}
