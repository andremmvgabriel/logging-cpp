#include <gabe/logging/logging.hpp>

// Typedefs just to agile the accessibility  of methods
typedef gabe::logging::SeverityLevel SevLvl;

void add_values_and_log(int val1, int val2) {
    int result = val1 + val2;
    LOG(SevLvl::DEBUG, "My addition: {} + {} = {}", val1, val2, result);
    LOG(SevLvl::DEBUG, "{:^20s} {:^4d} + {:^4d} = {:^4d}", "My addition:", val1, val2, result);
}

int main() {
    /*
    Overview:
        This example should cover how easy you can start logging.

        You have have to import the logging header file and you are good to go!

    Notes:
        The default logger created in the background is called "main". Also by default, the log file created by it has its name.
    */

    // Change the default log files location from "root" to "logs"
    SET_DEFAULT_LOGS_DIRECTORY("logs");

    // Change the default log severity from "INFO" to "TRACE"
    SET_DEFAULT_SEVERITY(SevLvl::TRACE);

    LOG(SevLvl::TRACE, "Testing TRACE from LOG function.");
    LOG(SevLvl::DEBUG, "Testing DEBUG from LOG function.");
    LOG(SevLvl::INFO, "Testing INFO from LOG function.");
    LOG(SevLvl::WARNING, "Testing WARNING from LOG function.");
    LOG(SevLvl::ERROR, "Testing ERROR from LOG function.");
    LOG(SevLvl::FATAL, "Testing FATAL from LOG function.");

    TRACE("Testing TRACE from TRACE function.");
    DEBUG("Testing DEBUG from DEBUG function.");
    INFO("Testing INFO from INFO function.");
    WARNING("Testing WARNING from WARNING function.");
    ERROR("Testing ERROR from ERROR function.");
    FATAL("Testing FATAL from FATAL function.");

    add_values_and_log(10, 40);
    
    return 0;
}
