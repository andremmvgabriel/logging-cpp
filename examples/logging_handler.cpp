#include <gabe/logging/logging.hpp>

// Typedefs just to agile the accessibility  of methods
typedef gabe::logging::SeverityLevel SevLvl;
typedef gabe::logging::LoggerHandler LogHdl;

void add_values_and_log(int val1, int val2) {
    int result = val1 + val2;
    LOG(SevLvl::DEBUG, "My addition: {} + {} = {}", val1, val2, result);
    LOG(SevLvl::DEBUG, "{:^20s} {:^4d} + {:^4d} = {:^4d}", "My addition:", val1, val2, result);
}

void log_with_copy_handler(LogHdl logger) {
    logger.trace("Testing {:^10s} logs from a {:^10s} handler.", "TRACE", "COPY");
    logger.debug("Testing {:^10s} logs from a {:^10s} handler.", "DEBUG", "COPY");
    logger.info("Testing {:^10s} logs from a {:^10s} handler.", "INFO", "COPY");
    logger.warning("Testing {:^10s} logs from a {:^10s} handler.", "WARNING", "COPY");
    logger.error("Testing {:^10s} logs from a {:^10s} handler.", "ERROR", "COPY");
    logger.fatal("Testing {:^10s} logs from a {:^10s} handler.", "FATAL", "COPY");
}

void log_with_pointer_handler(LogHdl *logger) {
    logger->trace("Testing {:^10s} logs from a {:^10s} handler.", "TRACE", "POINTER");
    logger->debug("Testing {:^10s} logs from a {:^10s} handler.", "DEBUG", "POINTER");
    logger->info("Testing {:^10s} logs from a {:^10s} handler.", "INFO", "POINTER");
    logger->warning("Testing {:^10s} logs from a {:^10s} handler.", "WARNING", "POINTER");
    logger->error("Testing {:^10s} logs from a {:^10s} handler.", "ERROR", "POINTER");
    logger->fatal("Testing {:^10s} logs from a {:^10s} handler.", "FATAL", "POINTER");
}

void log_with_reference_handler(LogHdl &logger) {
    logger.trace("Testing {:^10s} logs from a {:^10s} handler.", "TRACE", "REFERENCE");
    logger.debug("Testing {:^10s} logs from a {:^10s} handler.", "DEBUG", "REFERENCE");
    logger.info("Testing {:^10s} logs from a {:^10s} handler.", "INFO", "REFERENCE");
    logger.warning("Testing {:^10s} logs from a {:^10s} handler.", "WARNING", "REFERENCE");
    logger.error("Testing {:^10s} logs from a {:^10s} handler.", "ERROR", "REFERENCE");
    logger.fatal("Testing {:^10s} logs from a {:^10s} handler.", "FATAL", "REFERENCE");
}

void log_with_handler_recalling() {
    // Gets the logger with "logging_handler_example" name. (It will be given the one created previously. You don't have to reconfigure again)
    LogHdl logger = GET_LOGGER("logging_handler_example");

    logger.trace("Testing {:^10s} logs from a {:^10s} handler.", "TRACE", "RECALL");
    logger.debug("Testing {:^10s} logs from a {:^10s} handler.", "DEBUG", "RECALL");
    logger.info("Testing {:^10s} logs from a {:^10s} handler.", "INFO", "RECALL");
    logger.warning("Testing {:^10s} logs from a {:^10s} handler.", "WARNING", "RECALL");
    logger.error("Testing {:^10s} logs from a {:^10s} handler.", "ERROR", "RECALL");
    logger.fatal("Testing {:^10s} logs from a {:^10s} handler.", "FATAL", "RECALL");
}

int main() {
    /*
    Overview:
        This example should cover how to use the logging handler object.

    Notes:
    */

    // Gets the logger with "logging_handler_example" name. (It creates it since it does not exist yet)
    LogHdl logger = GET_LOGGER("logging_handler_example");

    // Quick logger configuration (just to change the default values)
    logger.basic_config(
        SevLvl::DEBUG, // Log severity as "DEBUG"
        "logs", // Logs directory as "logs", relative path
        "logging_handler_example" // Log file name
    );

    // The previous configuration line is the same as executing the following 3
    logger.set_severity(SevLvl::DEBUG);
    logger.set_logs_location("logs");
    logger.set_logs_file_name("logging_handler_example");

    // Logging using LoggerHandler object
    logger.trace("Function call: logger.trace().");
    logger.debug("Function call: logger.debug().");
    logger.info("Function call: logger.info().");
    logger.warning("Function call: logger.warning().");
    logger.error("Function call: logger.error().");
    logger.fatal("Function call: logger.fatal().");

    logger.log(SevLvl::TRACE, "Function call: logger.log(TRACE)");
    logger.log(SevLvl::DEBUG, "Function call: logger.log(DEBUG)");
    logger.log(SevLvl::INFO, "Function call: logger.log(INFO)");
    logger.log(SevLvl::WARNING, "Function call: logger.log(WARNING)");
    logger.log(SevLvl::ERROR, "Function call: logger.log(ERROR)");
    logger.log(SevLvl::FATAL, "Function call: logger.log(FATAL)");

    // Logging within functions
    log_with_copy_handler(logger);
    log_with_pointer_handler(&logger);
    log_with_reference_handler(logger);
    log_with_handler_recalling();
    
    return 0;
}
