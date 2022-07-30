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
             * %smonth -> Adds the name of the month from which the log was done. Result if a string of 3 characters. Example: Jul (July).
             * %day -> Adds the number of the day of the month from which the log was done. Result is a string of 2 digits. Example: 30.
             * %week -> Adds the number of the week day from which the log was done. Result is a string of a single digit. Example: 1 (Monday).
             * %sweek -> Adds the name of the week day from which the log was done. Result is a string of 3 characters. Example: Mon (Monday).
             */
            class Calendar : public MultiFormatter
            {
            protected:
                /**
                 * @brief Calendar Internal Formatter object.
                 * 
                 * This is an abstract class which is used to create all the specialized (childs) formatters needed in the Calendar.
                 */
                class InternalFormatter : public Formatter
                {
                protected:
                    /**
                     * @brief Pointer to calendar data structure.
                     */
                    std::tm *_calendar = nullptr;
                
                public:
                    /**
                     * @brief Construct a new Internal Formatter object.
                     */
                    InternalFormatter();

                    /**
                     * @brief Construct a new Internal Formatter object.
                     * 
                     * @param type Formatter type/name.
                     * @param key Formatting key.
                     * @param calendar Pointer to calendar data structure.
                     */
                    InternalFormatter(const std::string &type, const std::string &key, std::tm *calendar);
                };

                /**
                 * @brief Year Formatter object.
                 * 
                 * This class objective is to format a log message with the year from which the log was created.
                 */
                class Year : public InternalFormatter
                {
                protected:
                    /**
                     * @brief Gets the year from the calendar info structure formatted as a string with 4 digits.
                     * 
                     * @return std::string Formatted year.
                     */
                    std::string _get_year();

                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is meant to be overritten and design to include all the needed methods to format the log message.
                     * 
                     * @return std::string Formatted year.
                     */
                    virtual std::string _format() override;

                public:
                    /**
                     * @brief Construct a new Year object.
                     */
                    Year();

                    /**
                     * @brief Construct a new Year object.
                     * 
                     * @param key Formatting key.
                     * @param calendar Pointer to calendar data structure.
                     */
                    Year(const std::string &key, std::tm *calendar);
                };

                /**
                 * @brief Month Formatter object.
                 * 
                 * This class objective is to format a log message with the month from which the log was created.
                 */
                class Month : public InternalFormatter
                {
                protected:
                    /**
                     * @brief List of the 12 months acronyms. Every acronym is composed by 3 characters, capitalized.
                     */
                    std::string _months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dec"};
                
                protected:
                    /**
                     * @brief Gets the month from the calendar info structure formatted as a string with 2 digits.
                     * 
                     * @return std::string Formatted month.
                     */
                    std::string _get_month();

                    /**
                     * @brief Gets the month from the calendar info structure formatted as a string with 3 characters.
                     * 
                     * @return std::string Formatted month.
                     */
                    std::string _get_month_str();

                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is meant to be overritten and design to include all the needed methods to format the log message.
                     * 
                     * @return std::string Formatted month.
                     */
                    virtual std::string _format() override;

                public:
                    /**
                     * @brief Construct a new Month object.
                     */
                    Month();

                    /**
                     * @brief Construct a new Month object.
                     * 
                     * @param key Formatting key.
                     * @param calendar Pointer to calendar data structure.
                     */
                    Month(const std::string &key, std::tm *calendar);
                };

                /**
                 * @brief Day Formatter object.
                 * 
                 * This class objective is to format a log message with the day from which the log was created.
                 */
                class Day : public InternalFormatter
                {
                protected:
                    /**
                     * @brief Gets the day from the calendar info structure formatted as a string with 2 digits.
                     * 
                     * @return std::string Formatted day.
                     */
                    std::string _get_day();

                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is meant to be overritten and design to include all the needed methods to format the log message.
                     * 
                     * @return std::string Formatted day.
                     */
                    virtual std::string _format() override;
                
                public:
                    /**
                     * @brief Construct a new Day object.
                     */
                    Day();

                    /**
                     * @brief Construct a new Day object.
                     * 
                     * @param key Formatting key.
                     * @param calendar Pointer to calendar data structure.
                     */
                    Day(const std::string &key, std::tm *calendar);
                };

                /**
                 * @brief Week Formatter object.
                 * 
                 * This class objective is to format a log message with the week from which the log was created.
                 */
                class Week : public InternalFormatter
                {
                protected:
                    /**
                     * @brief List of the 7 week days acronyms. Every acronym is composed by 3 characters, capitalized.
                     */
                    std::string _week_days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
                
                protected:
                    /**
                     * @brief Gets the week day from the calendar info structure formatted as a string with 1 digit.
                     * 
                     * @return std::string Formatted week day.
                     */
                    std::string _get_week_day();

                    /**
                     * @brief Gets the week day from the calendar info structure formatted as a string with 3 characters.
                     * 
                     * @return std::string Formatted week day.
                     */
                    std::string _get_week_day_str();

                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is meant to be overritten and design to include all the needed methods to format the log message.
                     * 
                     * @return std::string Formatted week day.
                     */
                    virtual std::string _format() override;

                public:
                    /**
                     * @brief Construct a new Week object.
                     */
                    Week();

                    /**
                     * @brief Construct a new Week object.
                     * 
                     * @param key Formatting key.
                     * @param calendar Pointer to calendar data structure.
                     */
                    Week(const std::string &key, std::tm *calendar);
                };

            protected:
                /**
                 * @brief Calendar data structure as pointer variable.
                 */
                std::tm *_calendar = new std::tm();
            
            public:
                /**
                 * @brief Construct a new Calendar object.
                 */
                Calendar();
                
                /**
                 * @brief Destroy the Calendar object.
                 */
                ~Calendar();

                /**
                 * @brief Abstract method to format the log message.
                 * 
                 * This method is not meant to be overritten unless it is necessary to perform some extra steps before the actual formatting. If so, this function should be overritten and its additional behaviour inserted, finalizing with calling of the abstract function.
                 * 
                 * This function does not output the formatted log message. The log message is given as a reference instead, which allows its formatting on the given string.
                 */
                virtual void format(std::string &message) override;
            };
        }
    }
}
