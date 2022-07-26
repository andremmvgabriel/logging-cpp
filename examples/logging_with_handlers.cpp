#include <gabe/logging/logging.hpp>
#include <gabe/logging/handlers/ConsoleStdOutHandler.hpp>
#include <gabe/logging/handlers/SizeRotatingFileHandler.hpp>
#include <gabe/logging/handlers/TimeRotatingFileHandler.hpp>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// Typedefs just to agile the accessibility of methods
typedef gabe::logging::SeverityLevel SevLvl;
typedef gabe::logging::LoggerHandler LogHdl;
typedef gabe::logging::handlers::ConsoleStdOutHandler ConsHan;
typedef gabe::logging::handlers::SizeRotatingFileHandler SizeHan;
typedef gabe::logging::handlers::TimeRotatingFileHandler TimeHan;

void using_size_rotating_file_handler() {
    // Gets the logger
    LogHdl logger = GET_LOGGER("logging_with_handlers-size");

    // Creates the size handler
    SizeHan size_handler(200); // 200 bytes for each file
    logger.add_handler(size_handler);

    // Log!
    logger.info("This hypothetic string has exactly 110 bytes, and its purpose it to fill the log file with more and more data."); // Should be in the first log file. Log file size = 110 + Formatters
    logger.info("This hypothetic string has exactly 110 bytes, and its purpose it to fill the log file with more and more data."); // Should be in the first log file. Log file size = 220 + Formatters. Since it reached the target size, a new log file should be created.
    logger.info("This hypothetic string has exactly 110 bytes, and its purpose it to fill the log file with more and more data."); // Should be in the second log file. Log file size = 110.
}

void using_time_rotating_file_handler() {
    // Gets the logger
    LogHdl logger = GET_LOGGER("logging_with_handlers-time");

    // Creates the time handler
    TimeHan time_handler("m"); // 1 minute for each file
    logger.add_handler(time_handler);

    // These logs should appear in the first log file
    logger.trace("Log in the first log file.");
    logger.debug("Log in the first log file.");
    logger.info("Log in the first log file.");
    logger.warning("Log in the first log file.");
    logger.error("Log in the first log file.");
    logger.fatal("Log in the first log file.");

    sleep(61);

    logger.trace("Log in the second log file.");
    logger.debug("Log in the second log file.");
    logger.info("Log in the second log file.");
    logger.warning("Log in the second log file.");
    logger.error("Log in the second log file.");
    logger.fatal("Log in the second log file.");

    sleep(61);

    logger.trace("Log in the third log file.");
    logger.debug("Log in the third log file.");
    logger.info("Log in the third log file.");
    logger.warning("Log in the third log file.");
    logger.error("Log in the third log file.");
    logger.fatal("Log in the third log file.");
}

void using_console_rotating_file_handler() {
    // Gets the logger
    LogHdl logger = GET_LOGGER("logging_with_handlers-stdout");

    // Creates the console stdout handler
    ConsHan console_handler;
    logger.add_handler(console_handler);

    // Log!
    logger.info("First message to appear in console!");
    logger.info("Second message to appear in console!");
    logger.warning("Third message to appear in console!");
    logger.fatal("Ok, last message to appear in console...");
}

int main() {
    /*
    Overview:
        This example should cover how to use the library handlers.
    
    Note:
        In the current version there is an issue handling a file with multiple handlers.
    */

    SET_DEFAULT_LOGS_DIRECTORY("logs");

    using_size_rotating_file_handler();
    using_time_rotating_file_handler();
    using_console_rotating_file_handler();

    return 0;
}
