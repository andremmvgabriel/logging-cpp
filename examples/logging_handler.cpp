#include <gabe/logging/logging.hpp>

typedef gabe::logging::SeverityLevel SevLvl;

int main() {
    /*
    Overview:
    Notes:
    */

    // 
    gabe::logging::LoggerHandler logger = GET_LOGGER("logging_handler_example");

    // Quick logger configuration (just to change the default values)
    logger.basic_config(
        SevLvl::DEBUG, // Log severity as "DEBUG"
        "logs", // Logs directory as "logs", relative path
        "logging_handler_example" // Log file name
    );

    // The previous line is the same as executing the following 3
    logger.set_severity(SevLvl::DEBUG);
    logger.set_logs_location("logs");
    logger.set_logs_file_name("logging_handler_example");

    // Logging using specific
    logger.trace("Testing TRACE from LOG function.");
    logger.debug("Testing DEBUG from LOG function.");
    logger.info("Testing INFO from LOG function.");
    logger.warning("Testing WARNING from LOG function.");
    logger.error("Testing ERROR from LOG function.");
    logger.fatal("Testing FATAL from LOG function.");

    // LOG(SevLvl::TRACE, "Testing TRACE from LOG function.");
    // LOG(SevLvl::DEBUG, "Testing DEBUG from LOG function.");
    // LOG(SevLvl::INFO, "Testing INFO from LOG function.");
    // LOG(SevLvl::WARNING, "Testing WARNING from LOG function.");
    // LOG(SevLvl::ERROR, "Testing ERROR from LOG function.");
    // LOG(SevLvl::FATAL, "Testing FATAL from LOG function.");

    // TRACE("Testing TRACE from TRACE function.");
    // DEBUG("Testing DEBUG from DEBUG function.");
    // INFO("Testing INFO from INFO function.");
    // WARNING("Testing WARNING from WARNING function.");
    // ERROR("Testing ERROR from ERROR function.");
    // FATAL("Testing FATAL from FATAL function.");
    
    return 0;
}
