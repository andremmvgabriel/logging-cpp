#include <logging.hpp>

int main()
{
    logging::Logger logger;

    logging::Logger logger2( {
        "../logs/",
        "log_file_name",
        1000,
        30,
        false,
        logging::opts::LogTemplate::SEV_MSG_TIME,
        logging::opts::TimestampTemplate::CALENDAR_YEAR_TIME
    } );

    logger.init();
    logger2.init();

    logger2.write_log<logging::opts::TextType::HEADER>(logging::Severity::DEBUG, "This is one of the best messages the logger will receive.");
    logger2.write_log<logging::opts::TextType::SUB_HEADER>(logging::Severity::DEBUG, "However, I managed to do a better one!");
    logger2.write_log(logging::Severity::FATAL, "FALATITY message!");
    logger2.write_log(logging::Severity::FATAL, "The previous message was so small, i needed to construct a new one. CARAAAAAAAAAAAAAAI message!");

    return 0;
}