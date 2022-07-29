#pragma once

#include <string>

#include <gabe/logging/Manager.hpp>
#include <gabe/logging/SeverityLevel.hpp>

/**
 * @brief Get the logging internal manager.
 * 
 * This private method returns the internal logging manager object that is static and global to all the logging library.
 * 
 * @note As the function name suggests, this function is private and is not intended to be used.
 * 
 * @return gabe::logging::Manager* 
 */
extern gabe::logging::Manager* _get_internal_manager();

/**
 * @brief Set the default logger name.
 * 
 * Changes the current logger name that is used by default with the logging global methods. 
 * 
 * @note The default logger name is "main".
 * 
 * @param logger_name Name of the logger you want to set as default.
 */
void SET_DEFAULT_LOGGER(const std::string &logger_name);

/**
 * @brief Set the default state of chained logs variable.
 * 
 * Changes the default chained logs boolean value. This variable only affects the creation of new loggers and not the ones that already exist.
 * 
 * @param allow_chained Boolean variable that enables/disables chained logging.
 */
void SET_DEFAULT_CHAINED_LOGS(bool allow_chained);

/**
 * @brief Set the default severity variable.
 * 
 * Changes the default severity value. This variable only affects the creation of new loggers and not the ones that already exist.
 * 
 * @param severity Default severity variable that will be used on new loggers creation.
 */
void SET_DEFAULT_SEVERITY(const gabe::logging::SeverityLevel &severity);

/**
 * @brief Set the default logs directory variable.
 * 
 * Changes the default logs directory path. This variable only affects the creation of new loggers and not the ones that already exist.
 * 
 * @param path Default path variable that will be used on new loggers creation.
 */
void SET_DEFAULT_LOGS_DIRECTORY(const std::string &path);

/**
 * @brief Set the default log layout variable.
 * 
 * Changes the default log layout format. This variable only affects the creation of new loggers and not the ones that already exist.
 * 
 * @note Log layouts should change depending on the formatters you are using. please check Formatters for a better understanding.
 * 
 * @param log_layout Default log layout variable that will be used on new loggers creation.
 */
void SET_DEFAULT_LOG_LAYOUT(const std::string &log_layout);

/**
 * @brief Get a handler of the target logger.
 * 
 * Once called, the internal logging manager searches and returns a handler for the target logger.
 * 
 * @note If the specified logger does not exist, the internal manager ensures its creation (with the default settings) and returns it to you.
 * 
 * @param logger_name Name of the target logger.
 * @return gabe::logging::LoggerHandler Logger object as a handler object.
 */
gabe::logging::LoggerHandler GET_LOGGER(const std::string &logger_name);

/**
 * @brief Adds a log formatter to the default logger.
 * 
 * Adds a log formatter object into the default logger. This formatter must be a child of the Formatter abstract object.
 * 
 * @tparam FormatterT Formatter type.
 * @param formatter Formatter object.
 */
template<typename FormatterT>
void ADD_FORMATTER(const FormatterT &formatter) {
    // Gets the internal logging manager
    gabe::logging::Manager* manager = _get_internal_manager();

    // Adds the formatter to the default logger
    manager->add_formatter(formatter);
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
void ADD_HANDLER(const HandlerT &handler) {
    // Gets the internal logging manager
    gabe::logging::Manager* manager = _get_internal_manager();
    
    // Adds the handler to the default logger
    manager->add_handler(handler);
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
void LOG(const gabe::logging::SeverityLevel &severity, const std::string &message, Args... args) {
    // Gets the internal logging manager
    gabe::logging::Manager* manager = _get_internal_manager();

    // Perfoms the logging into the default logger
    manager->log(severity, message, args...);
}

/**
 * @brief Logs a message with TRACE severity into default logger.
 * 
 * Logs a message with TRACE severity into default logger. This function does only affect the default logger that can be defined through the SET_DEFAULT_LOGGER function.
 * 
 * @tparam Args Types of the additional log arguments.
 * @param message Log message.
 * @param args Additional log arguments.
 */
template<typename ... Args>
void TRACE(const std::string &message, Args... args) {
    // Gets the internal logging manager
    gabe::logging::Manager* manager = _get_internal_manager();

    // Perfoms the logging into the default logger
    manager->log(gabe::logging::SeverityLevel::TRACE, message, args...);
}

/**
 * @brief Logs a message with DEBUG severity into default logger.
 * 
 * Logs a message with DEBUG severity into default logger. This function does only affect the default logger that can be defined through the SET_DEFAULT_LOGGER function.
 * 
 * @tparam Args Types of the additional log arguments.
 * @param message Log message.
 * @param args Additional log arguments.
 */
template<typename ... Args>
void DEBUG(const std::string &message, Args... args) {
    // Gets the internal logging manager
    gabe::logging::Manager* manager = _get_internal_manager();

    // Perfoms the logging into the default logger
    manager->log(gabe::logging::SeverityLevel::DEBUG, message, args...);
}

/**
 * @brief Logs a message with INFO severity into default logger.
 * 
 * Logs a message with INFO severity into default logger. This function does only affect the default logger that can be defined through the SET_DEFAULT_LOGGER function.
 * 
 * @tparam Args Types of the additional log arguments.
 * @param message Log message.
 * @param args Additional log arguments.
 */
template<typename ... Args>
void INFO(const std::string &message, Args... args) {
    // Gets the internal logging manager
    gabe::logging::Manager* manager = _get_internal_manager();

    // Perfoms the logging into the default logger
    manager->log(gabe::logging::SeverityLevel::INFO, message, args...);
}

/**
 * @brief Logs a message with WARNING severity into default logger.
 * 
 * Logs a message with WARNING severity into default logger. This function does only affect the default logger that can be defined through the SET_DEFAULT_LOGGER function.
 * 
 * @tparam Args Types of the additional log arguments.
 * @param message Log message.
 * @param args Additional log arguments.
 */
template<typename ... Args>
void WARNING(const std::string &message, Args... args) {
    // Gets the internal logging manager
    gabe::logging::Manager* manager = _get_internal_manager();

    // Perfoms the logging into the default logger
    manager->log(gabe::logging::SeverityLevel::WARNING, message, args...);
}

/**
 * @brief Logs a message with ERROR severity into default logger.
 * 
 * Logs a message with ERROR severity into default logger. This function does only affect the default logger that can be defined through the SET_DEFAULT_LOGGER function.
 * 
 * @tparam Args Types of the additional log arguments.
 * @param message Log message.
 * @param args Additional log arguments.
 */
template<typename ... Args>
void ERROR(const std::string &message, Args... args) {
    // Gets the internal logging manager
    gabe::logging::Manager* manager = _get_internal_manager();

    // Perfoms the logging into the default logger
    manager->log(gabe::logging::SeverityLevel::ERROR, message, args...);
}

/**
 * @brief Logs a message with FATAL severity into default logger.
 * 
 * Logs a message with FATAL severity into default logger. This function does only affect the default logger that can be defined through the SET_DEFAULT_LOGGER function.
 * 
 * @tparam Args Types of the additional log arguments.
 * @param message Log message.
 * @param args Additional log arguments.
 */
template<typename ... Args>
void FATAL(const std::string &message, Args... args) {
    // Gets the internal logging manager
    gabe::logging::Manager* manager = _get_internal_manager();

    // Perfoms the logging into the default logger
    manager->log(gabe::logging::SeverityLevel::FATAL, message, args...);
}
