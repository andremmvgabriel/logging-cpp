#include <logging.hpp>

// You can make typedefs to make your life easier
typedef gabe::logging::Logger Logger;
typedef gabe::logging::opts::LogTemplate LogTemplate;
typedef gabe::logging::opts::TimestampTemplate TimeTemplate;
typedef gabe::logging::opts::TextType TextType;
typedef gabe::logging::Severity logSev;

int main()
{
    Logger logger(logSev::DEBUG);

    Logger logger2(
        logSev::DEBUG,
        {
            "logs/",
            "log_file_name",
            1000,
            30,
            false,
            LogTemplate::SEV_MSG_TIME,
            TimeTemplate::CALENDAR_YEAR_TIME
        }
    );

    logger.init();
    logger.log<TextType::HEADER>(logSev::DEBUG, "This is one of the best messages the logger will receive.");
    logger.log<TextType::SUB_HEADER>(logSev::DEBUG, "However, I managed to do a better one!");
    logger.log(logSev::FATAL, "FALATITY message!");
    logger.log(logSev::FATAL, "The previous message was so small, i needed to construct a new one. CARAAAAAAAAAAAAAAI message!");

    logger2.init();

    logger2.info<TextType::HEADER>("This is one of the best messages the logger will receive.");
    logger2.debug<TextType::SUB_HEADER>("However, I managed to do a better one!");
    logger2.fatal("FALATITY message!");
    logger2.fatal("The previous message was so small, i needed to construct a new one. CARAAAAAAAAAAAAAAI message!");

    return 0;
}