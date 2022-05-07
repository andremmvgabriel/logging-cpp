#pragma once

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
        
        public:
            Manager();
            ~Manager();

            void log(const std::string &logger_name, const SeverityLevel &severity, const std::string &message);

            LoggerHandler get_logger(const std::string &logger_name);
            void setup_logger(const std::string &name);
        };
    }
}
