#include <logging.hpp>

int main()
{
    logging::Logger logger;

    logging::Logger logger2( {
        "../logs/",
        "log_file_name",
        1000,
        -1,
        false
    } );

    logger.init();

    return 0;
}