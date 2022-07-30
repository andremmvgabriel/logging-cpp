#pragma once

#include <string>
#include <ctime>
#include <unordered_map>

#include <gabe/logging/formatters/MultiFormatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            /**
             * @brief Calendar Multi-Formatter object.
             * 
             * This class is meant to be instantiated and given to a Logger object. It's objective is to format log messages, adding calendar information to it. To be able to format the log message, the user has to make sure that log layout contains the calendar format keywords. These keywords are:
             * 
             * %year -> Adds the year from which the log was done. Result is a string of 4 digits. Example: 2022.
             * %month -> Adds the number of the month from which the log was done. Result is a string of 2 digits. Example: 07 (July).
             * %smonth -> Adds the name of the month from which the log was done. Result if a string of 3 characters. Example: jul (July).
             * %day -> Adds the number of the day of the month from which the log was done. Result is a string of 2 digits. Example: 30.
             * %week -> Adds the number of the week day from which the log was done. Result is a string of a single digit. Example: 1 (Monday).
             * %sweek -> Adds the name of the week day from which the log was done. Result is a string of 3 characters. Example: mon (Monday).
             */
            class Calendar : public MultiFormatter
            {
            protected:
                /**
                 * @brief Calendar Internal Formatter object.
                 * 
                 */
                class InternalFormatter : public Formatter
                {
                protected:
                    std::tm *_calendar = nullptr;
                
                public:
                    InternalFormatter();
                    InternalFormatter(const std::string &type, const std::string &key, std::tm *calendar);
                };

                class Year : public InternalFormatter
                {
                protected:
                    std::string _get_year();

                public:
                    Year();
                    Year(const std::string &key, std::tm *calendar);

                    virtual std::string _format() override;
                };

                class Month : public InternalFormatter
                {
                protected:
                    std::string _months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dec"};
                
                protected:
                    std::string _get_month();
                    std::string _get_month_str();

                    virtual std::string _format() override;

                public:
                    Month();
                    Month(const std::string &key, std::tm *calendar);
                };

                class Day : public InternalFormatter
                {
                protected:
                    std::string _get_day();

                    virtual std::string _format() override;
                
                public:
                    Day();
                    Day(const std::string &key, std::tm *calendar);
                };

                class Week : public InternalFormatter
                {
                protected:
                    std::string _week_days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
                
                protected:
                    std::string _get_week_day();
                    std::string _get_week_day_str();

                    virtual std::string _format() override;

                public:
                    Week();
                    Week(const std::string &key, std::tm *calendar);
                };

            protected:
                std::tm *_calendar = new std::tm();
            
            public:
                Calendar();
                ~Calendar();

                virtual void format(std::string &message) override;
            };
        }
    }
}
