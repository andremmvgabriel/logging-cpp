#pragma once

#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>

//typedef logging::Severity Severity;

namespace logging
{
    enum class Severity
    {
        TRACE   = 1,
        DEBUG   = 2,
        INFO    = 4,
        WARNING = 8,
        ERROR   = 16,
        FATAL   = 32
    };

    namespace opts
    {
        struct Settings
        {
            std::string logs_dir;
            std::string file_name;

            int max_file_size;
            int max_line_size;

            bool mult_line_logs;
        };
    }

    namespace utils
    {

    }

    class Logger
    {
    private:
        std::ofstream _log_file;
        /**<Log file.*/

        opts::Settings _settings = {
            "logs/",
            "log_file",
            5000000,
            -1,
            true
        };
        /**<Logging settings. It has default settings.*/

        bool _is_working = false;
        /**<Control variable for working status.*/

        int _files_counter = 0;
        /**<Control variable for counting created log files.*/

    private:
        bool _open_log_file();

    public:
        /**
         * @brief 
         * 
         */
        Logger();

        /**
         * @brief 
         * 
         * @param settings 
         */
        Logger(const opts::Settings& settings);

        /**
         * @brief Copy constructor.
         * 
         * This copy constructor is disabled.
         * 
         * @param logger Given Logger object to be copied.
         */
        Logger (const Logger& logger) = delete;

        /**
         * @brief Copy constructor
         * 
         * Creates a new Logger object, copying the contents from another Logger object.
         * 
         * @param logger Given Logger object to be copied.
         */
        Logger (Logger&& logger);

        /**
         * @brief Copy assignment.
         * 
         * This copy assignment is disabled.
         * 
         * @param logger Given Logger object to be copied.
         * @return Logger& New Logger object.
         */
        Logger& operator = (const Logger& logger) = delete;

        /**
         * @brief Copy assignment.
         * 
         * Allows the copy of one Logger object into a new Logger object with the usage of an equal (=) assignment.
         * 
         * @param logger Given Logger object to be copied.
         * @return Logger& New Logger object.
         */
        Logger& operator = (Logger&& logger);

        ~Logger();

        void init();
    };
}