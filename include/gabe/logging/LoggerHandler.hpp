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

            void log(const gabe::logging::SeverityLevel &severity, const std::string &message);

            template<typename HandlerT>
            void add_handler(const HandlerT& handler) {
                _logger->add_handler(handler);
            }
        };
    }
}
