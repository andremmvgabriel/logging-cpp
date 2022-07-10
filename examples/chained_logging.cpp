#include <gabe/logging/logging.hpp>

// Typedefs just to agile the accessibility  of methods
typedef gabe::logging::SeverityLevel SevLvl;
typedef gabe::logging::LoggerHandler LogHdl;

void default_chained_turn_on() {
    // Creates the loggers with parent - child hierarchy
    LogHdl logger_1 = GET_LOGGER("chained_logging_1");
    LogHdl logger_2 = GET_LOGGER("chained_logging_1.child_1");

    logger_1.info("Logging from parent logger. This log should only appear in parent.");
    logger_2.info("Logging from child logger. This log should appear in both child and parent.");
}

void default_chained_turn_off() {
    // Removes the default chained control variable
    SET_DEFAULT_CHAINED_LOGS(false);

    // Creates the loggers with parent - child hierarchy
    LogHdl logger_1 = GET_LOGGER("chained_logging_2");
    LogHdl logger_2 = GET_LOGGER("chained_logging_2.child_1");

    // This line will achieve the same as "SET_DEFAULT_CHAINED_LOGS(false)", but will only affect the logger instance, instead of every logger created (It is only used here for example purposes).
    logger_2.set_chained_logs(false);

    logger_1.info("Logging from parent logger. This log should only appear in parent.");
    logger_2.info("Logging from child logger. This log should only appear in child.");

    // Turns the default chained control variable again to true
    SET_DEFAULT_CHAINED_LOGS(true);
}

void more_complex_hierarchy() {
    // Creates the loggers with hierarchy
    LogHdl logger_1 = GET_LOGGER("chained_logging_3");
    LogHdl logger_2 = GET_LOGGER("chained_logging_3.child_1");
    LogHdl logger_3 = GET_LOGGER("chained_logging_3.child_2");
    LogHdl logger_4 = GET_LOGGER("chained_logging_3.child_1.grandchild_1");
    LogHdl logger_5 = GET_LOGGER("chained_logging_3.child_1.grandchild_2");
    LogHdl logger_6 = GET_LOGGER("chained_logging_3.child_2.grandchild_3");

    // Lets cut the relation that child_2 have with its parent
    logger_3.set_chained_logs(false);

    // Lets cut the relation that grandchild_2 have with its parent
    logger_5.set_chained_logs(false);

    // Now lets do the logging
    logger_1.info("Logging from parent logger. This log should only appear in parent.");
    logger_2.info("Logging from child_1 logger. This log should appear in both child_1 and parent.");
    logger_3.info("Logging from child_2 logger. This log should only appear in child_2.");
    logger_4.info("Logging from grandchild_1 logger. This log should appear in grandchild_1, child_1, and parent.");
    logger_5.info("Logging from grandchild_2 logger. This log should only appear in grandchild_2.");
    logger_6.info("Logging from grandchild_3 logger. This log should appear in both grandchild_3 and child_2.");
}

int main() {
    /*
    Overview:
        This example should cover how to use the logging handlers as a hierarchy.

    Notes:
        1) A child logger, such as "parent.child" will always be recognized as "parent.child". If you try to GET_LOGGER("child") you will get a different logger.
        2) Remember that if you want to change the name of the logs of each logger you can always proceed to use the "basic_config" or the individual "set" functions.
    */

   // Change the default log files location from "root" to "logs"
    SET_DEFAULT_LOGS_DIRECTORY("logs");

    default_chained_turn_on();
    default_chained_turn_off();
    more_complex_hierarchy();

    return 0;
}