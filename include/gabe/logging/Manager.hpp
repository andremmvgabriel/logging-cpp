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
            std::string _logs_directory;
            bool _chained_logs;

            std::mutex _manager_mutex;
        
        protected:
            std::string _find_parent_logger_name(const std::string &logger_name);
        
        public:
            Manager();
            ~Manager();

            void set_logs_directory(const std::string &path);
            void set_chained_logs(bool active);

            void log(const std::string &logger_name, const SeverityLevel &severity, const std::string &message);

            LoggerHandler get_logger(const std::string &logger_name);
            void setup_logger(const std::string &name, core::Logger* parent = nullptr);
        };
    }
}
