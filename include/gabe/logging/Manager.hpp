#pragma once

#include <mutex>
#include <string>
#include <unordered_map>

#include <gabe/logging/LoggerHandler.hpp>
#include <gabe/logging/core/Logger.hpp>
#include <gabe/logging/SeverityLevel.hpp>

namespace gabe {
    namespace logging {
        class Manager
        {
        private:
            std::unordered_map<std::string, core::Logger*> _loggers;

            std::mutex _manager_mutex;

            // Default settings
            std::string _default_logger;
            bool _default_chained_logs;
            SeverityLevel _default_severity;
            std::string _default_logs_directory;
            std::string _default_log_layout;
        
        protected:
            std::string _find_parent_logger_name(const std::string &logger_name);
        
        public:
            Manager();
            ~Manager();

            void set_default_logger(const std::string &logger_name);
            void set_default_chained_logs(bool allow_chained);
            void set_default_severity(const SeverityLevel &severity);
            void set_default_logs_directory(const std::string &path);
            void set_default_log_layout(const std::string &log_layout);

            template<typename FormatterT>
            void add_formatter(const FormatterT &formatter) {
                LoggerHandler logger = get_logger(_default_logger);
                logger.add_formatter(formatter);
            }

            template<typename HandlerT>
            void add_handler(const HandlerT &handler) {
                LoggerHandler logger = get_logger(_default_logger);
                logger.add_handler(handler);
            }

            template<typename ... Args>
            void log(const SeverityLevel &severity, const std::string &message, Args... args) {
                LoggerHandler logger = get_logger(_default_logger);
                logger.log(severity, message, args...);
            }

            LoggerHandler get_logger(const std::string &logger_name);
            void setup_logger(const std::string &name, core::Logger* parent = nullptr);
        };
    }
}
