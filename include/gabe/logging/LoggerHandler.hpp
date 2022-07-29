#pragma once

#include <gabe/logging/core/Logger.hpp>

namespace gabe {
    namespace logging {
        /**
         * @brief Logger Handler object.
         * 
         * This class is designed to carry a pointer of the actual Logger object created and shared by the internal logging manager. This design allows a more "safe" behaviour when using this logger object by copying or similar. 
         */
        class LoggerHandler
        {
        public:
            /**
             * @brief Pointer of the Logger object.
             */
            core::Logger *_logger = nullptr;
        
        public:
            /**
             * @brief Construct a new Logger Handler object.
             * 
             * Default constructor. This is not meant to be used, unless you create a logger handler object variable that is meant to be assigned to a different logger handler later on. Otherwise, an object created with this cosntructor will not log at all.
             */
            LoggerHandler();

            /**
             * @brief Construct a new Logger Handler object.
             * 
             * Logger pointer constructor. This is the constructor meant to be used to create a Logger Handler that is able to log. However, this constructor requires the creation of a Logger object pointer.
             * 
             * @param logger Pointer of the Logger object.
             */
            LoggerHandler(core::Logger *logger);

            /**
             * @brief Construct a new Logger Handler object.
             * 
             * Copy constructor. This constructor is the one called when you create a Logger Handler from another Logger Handler object.
             * 
             * @param logger_handler Other Logger Handler object that will be copied.
             */
            LoggerHandler(const LoggerHandler &logger_handler);

            /**
             * @brief Equal assignment operation.
             * 
             * This function allows to manager the Logger Handler object internal behaviour once a Logger Handler variable is assigned to another.
             * 
             * @param logger_handler Assigned Logger Handler. 
             * @return LoggerHandler& Created Logger Handler.
             */
            LoggerHandler& operator=(const LoggerHandler &logger_handler);

            /**
             * @brief Get the pointer of the internal Logger object.
             * 
             * @return core::Logger* Logger object.
             */
            core::Logger* ptr();

            /**
             * @brief Set the name of the logs file.
             * 
             * @param file_name Name of the log file.
             */
            void set_logs_file_name(const std::string &file_name);

            /**
             * @brief Get the name of the logs file.
             * 
             * @return std::string Name of the log file.
             */
            std::string get_logs_file_name();

            /**
             * @brief Set the state of the chained logs variable.
             * 
             * @param active State of the variable.
             */
            void set_chained_logs(bool active);

            /**
             * @brief Get the state of the chained logs variable.
             * 
             * @return bool State of the variable.
             */
            bool get_chained_logs();

            /**
             * @brief Set the severity level of the logger.
             * 
             * @param severity Severity level.
             */
            void set_severity(const SeverityLevel &severity);

            /**
             * @brief Get the severity level of the logger.
             * 
             * @return SeverityLevel Severity level.
             */
            SeverityLevel get_severity();

            /**
             * @brief Set the path to log files directory.
             * 
             * @param location Path to log files directory.
             */
            void set_logs_location(const std::string &location);

            /**
             * @brief Get the path to log files directory.
             * 
             * @return std::string Path to log files directory.
             */
            std::string get_logs_location();

            /**
             * @brief Set the layout of the logs.
             * 
             * @param log_layout Layout of the logs.
             */
            void set_log_layout(const std::string &log_layout);

            /**
             * @brief Get the layout of the logs.
             * 
             * @return std::string Layout of the logs.
             */
            std::string get_log_layout();

            /**
             * @brief Perform a basic configuration of the logger.
             * 
             * This function allows a quick and basic configuration of the internal Logger object.
             * 
             * If you prefer to, this function is the same as calling individually the functions set_severity, set_logs_location, and set_logs_file_name.
             * 
             * @param severity Severity level.
             * @param location Path to log files directory.
             * @param file_name Name of the log file.
             */
            void basic_config(const SeverityLevel &severity, const std::string &location, const std::string &file_name);

            /**
             * @brief Adds a log formatter to the logger.
             * 
             * Adds a log formatter object into the logger object. This formatter must be a child of the Formatter abstract object.
             * 
             * @tparam FormatterT Formatter type.
             * @param formatter Formatter object.
             */
            template<typename FormatterT>
            void add_formatter(const FormatterT &formatter) {
                _logger->add_formatter(formatter);
            }

            /**
             * @brief Adds a file handler to the logger.
             * 
             * Adds a file handler object into the logger object. This handler must be a child of the Handler abstract object.
             * 
             * @tparam HandlerT Handler type.
             * @param handler Handler object.
             */
            template<typename HandlerT>
            void add_handler(const HandlerT& handler) {
                _logger->add_handler(handler);
            }

            /**
             * @brief Logs a message with a target severity into the logger.
             * 
             * @tparam Args Types of the additional log arguments.
             * @param severity Severity level of the log message.
             * @param message Log message.
             * @param args Additional log arguments.
             */
            template<typename ... Args>
            void log(const gabe::logging::SeverityLevel &severity, const std::string &message, Args... args) {
                _logger->log(severity, message, args...);
            }

            /**
             * @brief Logs a message with TRACE severity into the logger.
             * 
             * @tparam Args Types of the additional log arguments.
             * @param message Log message.
             * @param args Additional log arguments.
             */
            template<typename ... Args>
            void trace(const std::string &message, Args... args) {
                _logger->trace(message, args...);
            }

            /**
             * @brief Logs a message with DEBUG severity into the logger.
             * 
             * @tparam Args Types of the additional log arguments.
             * @param message Log message.
             * @param args Additional log arguments.
             */
            template<typename ... Args>
            void debug(const std::string &message, Args... args) {
                _logger->debug(message, args...);
            }

            /**
             * @brief Logs a message with INFO severity into the logger.
             * 
             * @tparam Args Types of the additional log arguments.
             * @param message Log message.
             * @param args Additional log arguments.
             */
            template<typename ... Args>
            void info(const std::string &message, Args... args) {
                _logger->info(message, args...);
            }

            /**
             * @brief Logs a message with WARNING severity into the logger.
             * 
             * @tparam Args Types of the additional log arguments.
             * @param message Log message.
             * @param args Additional log arguments.
             */
            template<typename ... Args>
            void warning(const std::string &message, Args... args) {
                _logger->warning(message, args...);
            }

            /**
             * @brief Logs a message with ERROR severity into the logger.
             * 
             * @tparam Args Types of the additional log arguments.
             * @param message Log message.
             * @param args Additional log arguments.
             */
            template<typename ... Args>
            void error(const std::string &message, Args... args) {
                _logger->error(message, args...);
            }

            /**
             * @brief Logs a message with FATAL severity into the logger.
             * 
             * @tparam Args Types of the additional log arguments.
             * @param message Log message.
             * @param args Additional log arguments.
             */
            template<typename ... Args>
            void fatal(const std::string &message, Args... args) {
                _logger->fatal(message, args...);
            }
        };
    }
}
