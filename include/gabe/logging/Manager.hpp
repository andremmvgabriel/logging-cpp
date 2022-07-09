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
        public:
            std::unordered_map<std::string, core::Logger*> _loggers;

            std::mutex _manager_mutex;

            // Default settings
            std::string _default_logger;
            bool _default_chained_logs;
            SeverityLevel _default_severity;
            std::string _default_logs_directory;
        
        protected:
            std::string _find_parent_logger_name(const std::string &logger_name);
        
        public:
            Manager();
            ~Manager();

            void set_default_logger(const std::string &logger_name);
            void set_default_chained_logs(bool allow_chained);
            void set_default_severity(const SeverityLevel &severity);
            void set_default_logs_directory(const std::string &path);

            template<typename ... Args>
            void log(const SeverityLevel &severity, const std::string &message, Args... args) {
                LoggerHandler logger = get_logger(_default_logger);
                logger.log(severity, message, args...);
            }

            template<typename ... Args>
            void log(const std::string &logger_name, const SeverityLevel &severity, const std::string &message, Args... args) {
                LoggerHandler logger = get_logger(logger_name);
                logger.log(severity, message, args...);
            }

            LoggerHandler get_logger(const std::string &logger_name);
            void setup_logger(const std::string &name, core::Logger* parent = nullptr);
        };
    }
}
