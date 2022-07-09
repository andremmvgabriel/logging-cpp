#pragma once

#include <string>

#include <gabe/logging/Manager.hpp>
#include <gabe/logging/SeverityLevel.hpp>

extern gabe::logging::Manager* _get_internal_manager();

void SET_DEFAULT_LOGGER(const std::string &logger_name);
void SET_DEFAULT_CHAINED_LOGS(bool allow_chained);
void SET_DEFAULT_SEVERITY(const gabe::logging::SeverityLevel &severity);
void SET_DEFAULT_LOGS_DIRECTORY(const std::string &path);

gabe::logging::LoggerHandler GET_LOGGER(const std::string &logger_name);

template<typename ... Args>
void LOG(const gabe::logging::SeverityLevel &severity, const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(severity, message, args...);
}

template<typename ... Args>
void LOG(const std::string &logger_name, const gabe::logging::SeverityLevel &severity, const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(logger_name, severity, message, args...);
}

template<typename ... Args>
void TRACE(const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(gabe::logging::SeverityLevel::TRACE, message, args...);
}

template<typename ... Args>
void TRACE(const std::string &logger_name, const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(logger_name, gabe::logging::SeverityLevel::TRACE, message, args...);
}

template<typename ... Args>
void DEBUG(const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(gabe::logging::SeverityLevel::TRACE, message, args...);
}

template<typename ... Args>
void DEBUG(const std::string &logger_name, const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(logger_name, gabe::logging::SeverityLevel::DEBUG, message, args...);
}

template<typename ... Args>
void INFO(const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(gabe::logging::SeverityLevel::INFO, message, args...);
}

template<typename ... Args>
void INFO(const std::string &logger_name, const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(logger_name, gabe::logging::SeverityLevel::INFO, message, args...);
}

template<typename ... Args>
void WARNING(const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(gabe::logging::SeverityLevel::WARNING, message, args...);
}

template<typename ... Args>
void WARNING(const std::string &logger_name, const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(logger_name, gabe::logging::SeverityLevel::WARNING, message, args...);
}

template<typename ... Args>
void ERROR(const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(gabe::logging::SeverityLevel::ERROR, message, args...);
}

template<typename ... Args>
void ERROR(const std::string &logger_name, const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(logger_name, gabe::logging::SeverityLevel::ERROR, message, args...);
}

template<typename ... Args>
void FATAL(const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(gabe::logging::SeverityLevel::FATAL, message, args...);
}

template<typename ... Args>
void FATAL(const std::string &logger_name, const std::string &message, Args... args) {
    gabe::logging::Manager* manager = _get_internal_manager();
    manager->log(logger_name, gabe::logging::SeverityLevel::FATAL, message, args...);
}