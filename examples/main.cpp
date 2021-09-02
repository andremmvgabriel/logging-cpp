#include <logging.hpp>

// You can make typedefs to make your life easier
typedef gabe::logging::Logger Logger;
typedef gabe::logging::opts::LogTemplate LogTemplate;
typedef gabe::logging::opts::TimestampTemplate TimeTemplate;
typedef gabe::logging::opts::TextType TextType;
typedef gabe::logging::Severity logSev;

int main()
{
    Logger logger;

    Logger logger2( {
        "../logs/",
        "log_file_name",
        1000,
        30,
        false,
        LogTemplate::SEV_MSG_TIME,
        TimeTemplate::CALENDAR_YEAR_TIME
    } );

    logger.init();
    logger2.init();

    logger2.write_log<TextType::HEADER>(logSev::DEBUG, "This is one of the best messages the logger will receive.");
    logger2.write_log<TextType::SUB_HEADER>(logSev::DEBUG, "However, I managed to do a better one!");
    logger2.write_log(logSev::FATAL, "FALATITY message!");
    logger2.write_log(logSev::FATAL, "The previous message was so small, i needed to construct a new one. CARAAAAAAAAAAAAAAI message!");

    return 0;
}