#pragma once

#include <mutex>
#include <string>
#include <unordered_map>

#include <gabe/logging/LoggerHandler.hpp>
#include <gabe/logging/core/Logger.hpp>
#include <gabe/logging/SeverityLevel.hpp>

namespace gabe {
    namespace logging {
        /**
         * @brief Logging Manager object.
         * 
         * This class is meant to manage all the loggers involved in an application that make use of the logging library.
         */
        class Manager
        {
        protected:
            /**
             * @brief Map of existent loggers.
             * 
             * Every logger that is created by the usage of the get logger function is inserted in this logger map, which is managed internally by the internal logging manager.
             */
            std::unordered_map<std::string, core::Logger*> _loggers;

            /**
             * @brief Mutex control variable for thread safe usage.
             */
            std::mutex _manager_mutex;

            // Default settings

            /**
             * @brief Name of the default logger.
             */
            std::string _default_logger;

            /**
             * @brief Allow/disallow chained logging by default.
             */
            bool _default_chained_logs;

            /**
             * @brief Severity of new created loggers by default.
             */
            SeverityLevel _default_severity;

            /**
             * @brief Directory path to write log files by default.
             */
            std::string _default_logs_directory;

            /**
             * @brief Logs layout by default.
             */
            std::string _default_log_layout;
        
        protected:
            /**
             * @brief Gets the name of the parent logger.
             * 
             * Gets the name of the parent logger by filtering the name of the given logger.
             * 
             * @param logger_name Name of the logger.
             * @return std::string Name of the parent logger.
             */
            std::string _get_parent_logger_name(const std::string &logger_name);
        
        public:
            /**
             * @brief Construct a new Manager object. Default constructor.
             */
            Manager();

            /**
             * @brief Destroy the Manager object.
             */
            ~Manager();

            /**
             * @brief Set the default logger name.
             * 
             * Changes the current logger name that is used by default with the logging methods. 
             * 
             * @note The default logger name is "main".
             * 
             * @param logger_name Name of the logger you want to set as default.
             */
            void set_default_logger(const std::string &logger_name);

            /**
             * @brief Set the default state of chained logs variable.
             * 
             * Changes the default chained logs boolean value. This variable only affects the creation of new loggers and not the ones that already exist.
             * 
             * @param allow_chained Boolean variable that enables/disables chained logging.
             */
            void set_default_chained_logs(bool allow_chained);

            /**
             * @brief Set the default severity variable.
             * 
             * Changes the default severity value. This variable only affects the creation of new loggers and not the ones that already exist.
             * 
             * @param severity Default severity variable that will be used on new loggers creation.
             */
            void set_default_severity(const SeverityLevel &severity);

            /**
             * @brief Set the default logs directory variable.
             * 
             * Changes the default logs directory path. This variable only affects the creation of new loggers and not the ones that already exist.
             * 
             * @param path Default path variable that will be used on new loggers creation.
             */
            void set_default_logs_directory(const std::string &path);

            /**
             * @brief Set the default log layout variable.
             * 
             * Changes the default log layout format. This variable only affects the creation of new loggers and not the ones that already exist.
             * 
             * @note Log layouts should change depending on the formatters you are using. please check Formatters for a better understanding.
             * 
             * @param log_layout Default log layout variable that will be used on new loggers creation.
             */
            void set_default_log_layout(const std::string &log_layout);

            /**
             * @brief Get a handler of the target logger.
             * 
             * Once called, the logger is searched and a handler of the target logger is returned.
             * 
             * @param logger_name Name of the target logger.
             * @return LoggerHandler Logger object as a handler object.
             */
            LoggerHandler get_logger(const std::string &logger_name);

            /**
             * @brief Creates the target logger.
             * 
             * @param name Name of the target logger.
             * @param parent Pointer of the parent of the target logger.
             */
            void setup_logger(const std::string &name, core::Logger* parent = nullptr);

            /**
             * @brief Adds a log formatter to the default logger.
             * 
             * Adds a log formatter object into the default logger. This formatter must be a child of the Formatter abstract object.
             * 
             * @tparam FormatterT Formatter type.
             * @param formatter Formatter object.
             */
            template<typename FormatterT>
            void add_formatter(const FormatterT &formatter) {
                // Gets the handler of the target logger
                LoggerHandler logger = get_logger(_default_logger);

                // Adds the formatter
                logger.add_formatter(formatter);
            }

            /**
             * @brief Adds a file handler to the default logger.
             * 
             * Adds a file handler object into the default logger. This handler must be a child of the HAndler abstract object.
             * 
             * @tparam HandlerT Handler type.
             * @param handler Handler object.
             */
            template<typename HandlerT>
            void add_handler(const HandlerT &handler) {
                // Gets the handler of the target logger
                LoggerHandler logger = get_logger(_default_logger);

                // Adds the handler
                logger.add_handler(handler);
            }

            /**
             * @brief Logs a message with a target severity into default logger.
             * 
             * Logs a message with a target severity into default logger. This function does only affect the default logger that can be defined through the SET_DEFAULT_LOGGER function.
             * 
             * @tparam Args Types of the additional log arguments.
             * @param severity Severity level of the log message.
             * @param message Log message.
             * @param args Additional log arguments.
             */
            template<typename ... Args>
            void log(const SeverityLevel &severity, const std::string &message, Args... args) {
                // Gets the handler of the target logger
                LoggerHandler logger = get_logger(_default_logger);

                // Performs the logging into the default logger
                logger.log(severity, message, args...);
            }
        };
    }
}
