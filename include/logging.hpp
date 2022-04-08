#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <mutex>

#include <filesystem>

namespace gabe
{
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
            enum class LogTemplate
            {
                SEV_MSG         = 0,    // [Severity] Message
                TIME_SEV_MSG    = 1,    // [Timestamp][Severity] Message
                SEV_TIME_MSG    = 2,    // [Severity][Timestamp] Message
                SEV_MSG_TIME    = 4     // [Severity] Message [Timestamp]
            };

            enum class TimestampTemplate
            {
                TIME,                   // [hh:mm::ss]
                CALENDAR_TIME,          // [Week Month Day][hh::mm::ss]
                CALENDAR_YEAR_TIME,     // [Week Month Day Year][hh::mm::ss]
            };

            enum class TextType
            {
                HEADER,
                SUB_HEADER,
                NORMAL
            };

            struct Settings
            {
                std::string logs_dir;
                std::string file_name;

                int max_file_size;
                int max_line_size;

                bool mult_line_logs;

                LogTemplate log_template;

                TimestampTemplate time_template;
            };
        }

        namespace utils
        {
            namespace dicts
            {
                static std::unordered_map<int, std::string> week_days {
                    {   0,  "Sun"   },    // Sunday
                    {   1,  "Mon"   },    // Monday
                    {   2,  "Tue"   },    // Tuesday
                    {   3,  "Wed"   },    // Wednesday
                    {   4,  "Thu"   },    // Thursday
                    {   5,  "Fri"   },    // Friday
                    {   6,  "Sat"   }     // Saturday
                };

                static std::unordered_map<int, std::string> months {
                    {   0,  "Jan"   },    // January
                    {   1,  "Feb"   },    // February
                    {   2,  "Mar"   },    // March
                    {   3,  "Apr"   },    // April
                    {   4,  "May"   },    // May
                    {   5,  "Jun"   },    // June
                    {   6,  "Jul"   },    // July
                    {   7,  "Ago"   },    // Agoust
                    {   8,  "Sep"   },    // September
                    {   9,  "Oct"   },    // October
                    {   10, "Nov"   },    // November
                    {   11, "Dec"   }     // December
                };

                static std::unordered_map<Severity, std::string> severity_levels {
                    {   Severity::TRACE,    "[ trace ]"     },
                    {   Severity::DEBUG,    "[ debug ]"     },
                    {   Severity::INFO,     "[ info  ]"     },
                    {   Severity::WARNING,  "[warning]"     },
                    {   Severity::ERROR,    "[ error ]"     },
                    {   Severity::FATAL,    "[ fatal ]"     }
                };
            }

            enum class TextAligment
            {
                LEFT,
                RIGHT,
                CENTER,
                JUSTIFY
            };

            namespace text_alignment
            {
                void left(std::string &msg, const int width);
                void right(std::string &msg, const int width);
                void center(std::string &msg, const int width);
                void justify(std::string &msg, const int width);
            };
        }

        class Logger
        {
        private:
            std::ofstream _log_file;
            /**<Log file.*/

            Severity _severity;
            /**<Logging severity.*/

            opts::Settings _settings = {
                "logs/",
                "log_file",
                5000000,
                -1,
                true,
                opts::LogTemplate::SEV_MSG,
                opts::TimestampTemplate::TIME
            };
            /**<Logging settings. It has default settings.*/

            bool _is_working = false;
            /**<Control variable for working status.*/

            int _files_counter = 0;
            /**<Control variable for counting created log files.*/

            std::mutex _log_mutex;
            /**<Mutex variable for thread safe.*/

        private:
            bool _open_log_file();
            void _check_file_size();
        
            std::string _make_timestamp();
            std::string _get_calendar(std::tm* tm, bool include_year);
            std::string _get_time(std::tm* tm);

            void _write_header_log(Severity severity, const std::string &message);
            void _write_subheader_log(Severity severity, const std::string &message);
            void _write_normal_log(Severity severity, const std::string &message);

            void _write_log(logging::Severity severity, const std::string &pre_message, std::string message, const std::string &pos_message, utils::TextAligment text_alignment);

            std::string _make_begin_log(logging::Severity severity);
            std::string _make_end_log();

        public:
            /**
             * @brief 
             * 
             */
            Logger();

            /**
             * @brief 
             * 
             */
            Logger(const Severity& severity);

            /**
             * @brief 
             * 
             * @param settings 
             */
            Logger(const Severity& severity, const opts::Settings& settings);

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

            template <opts::TextType TT = opts::TextType::NORMAL>
            void write_log(Severity severity, const std::string &message) {
                // Only logs if the logger was initialized
                if (_is_working) {
                    if (TT == opts::TextType::HEADER) { _write_header_log(severity, message); }
                    else if (TT == opts::TextType::SUB_HEADER) { _write_subheader_log(severity, message); }
                    else if (TT == opts::TextType::NORMAL) { _write_normal_log(severity, message); }
                    else { throw std::runtime_error("> Log text type was not recognized."); }
                }
            }

            void set_severity(const Severity& severity);
        };
    }
}