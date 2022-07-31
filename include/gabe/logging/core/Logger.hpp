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
            /**
             * @brief Logger object.
             * 
             * This class is the core class in this logging library. This is where all the logging is done and managed.
             */
            class Logger
            {
            protected:
                /**
                 * @brief Severity Formatter object.
                 * 
                 * This class objective is to format a log message with the severity of the log message.
                 */
                class SeverityFormatter : public formatters::Formatter
                {
                protected:
                    /**
                     * @brief Map of severity level to its string name.
                     */
                    std::unordered_map<SeverityLevel, std::string> _formatting = {
                        {   SeverityLevel::TRACE,   "TRACE"     },
                        {   SeverityLevel::DEBUG,   "DEBUG"     },
                        {   SeverityLevel::INFO,    "INFO"      },
                        {   SeverityLevel::WARNING, "WARNING"   },
                        {   SeverityLevel::ERROR,   "ERROR"     },
                        {   SeverityLevel::FATAL,   "FATAL"     }
                    };

                    /**
                     * @brief Log severity to format.
                     */
                    SeverityLevel _severity;
                
                protected:
                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is meant to be overritten and design to include all the needed methods to format the log message.
                     * 
                     * @return std::string Formatted severity.
                     */
                    virtual std::string _format() override;

                public:
                    /**
                     * @brief Construct a new Severity Formatter object.
                     */
                    SeverityFormatter();

                    /**
                     * @brief Set the severity level to format.
                     * 
                     * @param severity Severity level.
                     */
                    void set_severity(const SeverityLevel &severity);
                };

                /**
                 * @brief Message Formatter object.
                 * 
                 * This class objective is to format a log message with the message content.
                 */
                class MessageFormatter : public formatters::Formatter
                {
                protected:
                    /**
                     * @brief Message to format.
                     */
                    std::string _message;
                
                protected:
                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is meant to be overritten and design to include all the needed methods to format the log message.
                     * 
                     * @return std::string Formatted message.
                     */
                    virtual std::string _format() override;
                
                public:
                    /**
                     * @brief Construct a new Message Formatter object.
                     */
                    MessageFormatter();

                    /**
                     * @brief Set the message to format.
                     * 
                     * @param severity Message.
                     */
                    void set_message(const std::string &message);

                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is not meant to be overritten unless it is necessary to perform some extra steps before the actual formatting. If so, this function should be overritten and its additional behaviour inserted, finalizing with calling of the abstract function.
                     * 
                     * In the current case, the additional behaviour is to add the message content at the end of the log message if the formatting key is not found.
                     * 
                     * This function does not output the formatted log message. The log message is given as a reference instead, which allows its formatting on the given string.
                     */
                    virtual void format(std::string &message) override;
                };

            protected:
                /**
                 * @brief Logger's sink.
                 */
                Sink *_sink = nullptr;

                /**
                 * @brief Parent logger.
                 */
                Logger *_parent = nullptr;

                /**
                 * @brief Logger severity level.
                 */
                SeverityLevel _severity = SeverityLevel::INFO;

                /**
                 * @brief Logger Handlers map.
                 */
                std::unordered_map<std::string, handlers::Handler*> _handlers;

                /**
                 * @brief Logger Formatters map.
                 */
                std::unordered_map<std::string, formatters::Formatter*> _formatters;

                /**
                 * @brief Logs layout by default.
                 */
                std::string _log_layout = "[%sev] %msg";

                /**
                 * @brief Allow/disallow chained logging to its parent.
                 */
                bool _chained_logs = true;

                /**
                 * @brief Mutex control variable for thread safe usage.
                 */
                std::mutex _log_mutex;
            
            protected:
                /**
                 * @brief Filters the logger name.
                 * 
                 * This function basically replaces all the "." (hierarchy delimiter) to "-".
                 * 
                 * @param name Logger name.
                 * @return std::string Filtered logger name.
                 */
                std::string _filter_logger_name(std::string name);

                /**
                 * @brief Creates all the logger internal formatters.
                 */
                void _setup_internal_formatters();

                /**
                 * @brief Deletes the log sink.
                 */
                void _delete_sink();

                /**
                 * @brief Deletes all the created handlers.
                 */
                void _delete_handlers();

                /**
                 * @brief Deletes all the created formatters.
                 */
                void _delete_formatters();

                /**
                 * @brief Internal log function.
                 * 
                 * This is the function on all the fun happens. This function formats the log message with the specified log layout and handlers the log file if needed.
                 * 
                 * @param severity Log severity.
                 * @param message Log message.
                 */
                void _log(const SeverityLevel &severity, const std::string &message);

                /**
                 * @brief Evaluates all the handlers and rotates the log files.
                 * 
                 * @param message Log message.
                 */
                void _process_handlers(const std::string &message);

            public:
                /**
                 * @brief Construct a new Logger object.
                 */
                Logger();

                /**
                 * @brief Construct a new Logger object.
                 * 
                 * @param location Path to logs directory.
                 * @param name Log file name.
                 * @param parent Parent logger.
                 */
                Logger(const std::string &location, const std::string &name, Logger *parent);

                /**
                 * @brief Construct a new Logger object.
                 * 
                 * @param location Path to logs directory.
                 * @param name Log file name.
                 * @param severity Logger severity.
                 */
                Logger(const std::string &location, const std::string &name, const SeverityLevel &severity);

                /**
                 * @brief Construct a new Logger object.
                 * 
                 * @param location Path to logs directory.
                 * @param name Log file name.
                 * @param severity Logger severity.
                 * @param parent Parent logger.
                 */
                Logger(const std::string &location, const std::string &name, const SeverityLevel &severity, Logger *parent);

                /**
                 * @brief Destroy the Logger object.
                 */
                ~Logger();

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
                 * This function allows a quick and basic configuration of the Logger object.
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
                    // Creates a new pointer of the formatter type and which will copy the object of the given formatter.
                    FormatterT* formatter_copy = new FormatterT();
                    *formatter_copy = formatter;

                    // Deletes a previous formatter of the same type that was already given
                    if (_formatters.find(formatter.type()) != _formatters.end()) {
                        delete _formatters[formatter.type()];
                    }

                    // Adds the formatter to the map
                    _formatters[formatter.type()] = dynamic_cast<formatters::Formatter*>(formatter_copy);
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
                void add_handler(const HandlerT &handler) {
                    // Creates a new pointer of the handler type and which will copy the object of the given handler.
                    HandlerT* handler_copy = new HandlerT();
                    *handler_copy = handler;

                    // Updates the handler internal management variables
                    handler_copy->check_sink(_sink);
                    
                    // Deletes a previous handler of the same type that was already given
                    if (_handlers.find(handler.type()) != _handlers.end()) {
                        delete _handlers[handler.type()];
                    }

                    // Adds the handler to the map
                    _handlers[handler.type()] = dynamic_cast<handlers::Handler*>(handler_copy);
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
                void log(const SeverityLevel &severity, const std::string &message, Args... args) {
                    std::string formatted_message = fmt::format(message, args...);
                    _log(severity, formatted_message);
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
                    log(SeverityLevel::TRACE, message, args...);
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
                    log(SeverityLevel::DEBUG, message, args...);
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
                    log(SeverityLevel::INFO, message, args...);
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
                    log(SeverityLevel::WARNING, message, args...);
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
                    log(SeverityLevel::ERROR, message, args...);
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
                    log(SeverityLevel::FATAL, message, args...);
                }
            };
        }
    }
}
