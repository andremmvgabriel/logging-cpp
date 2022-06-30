#pragma once

#include <string>

#include <gabe/logging/Manager.hpp>
#include <gabe/logging/SeverityLevel.hpp>

void SET_LOGS_DIRECTORY(const std::string &path);

void LOG(const gabe::logging::SeverityLevel &severity, const std::string &message);
void LOG(const std::string &logger_name, const gabe::logging::SeverityLevel &severity, const std::string &message);

void TRACE(const std::string &message);
void TRACE(const std::string &logger_name, const std::string &message);

void DEBUG(const std::string &message);
void DEBUG(const std::string &logger_name, const std::string &message);

void INFO(const std::string &message);
void INFO(const std::string &logger_name, const std::string &message);

void WARNING(const std::string &message);
void WARNING(const std::string &logger_name, const std::string &message);

void ERROR(const std::string &message);
void ERROR(const std::string &logger_name, const std::string &message);

void FATAL(const std::string &message);
void FATAL(const std::string &logger_name, const std::string &message);

gabe::logging::LoggerHandler GET_LOGGER(const std::string &logger_name);
