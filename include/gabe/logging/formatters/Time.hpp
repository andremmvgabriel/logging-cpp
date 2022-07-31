#pragma once

#include <chrono>
#include <unordered_map>

#include <gabe/logging/formatters/MultiFormatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            /**
             * @brief Time Multi-Formatter object.
             * 
             * This class is meant to be instantiated and given to a Logger object. It's objective is to format log messages, adding time information to it. To be able to format the log message, the user has to make sure that log layout contains the time format keywords. These keywords are:
             * 
             * %hour -> Adds the hour from which the log was done. Result is a string of 2 digits. Example: 12.
             * %min -> Adds the minutes from which the log was done. Result is a string of 2 digits. Example: 07.
             * %sec -> Adds the seconds from which the log was done. Result if a string of 2 digits. Example: 59.
             * %ms -> Adds the milliseconds from which the log was done. Result is a string of 3 digits. Example: 300.
             * %epoch -> Adds the epoch timestamp from which the log was done. Result is a string of 10 digits. Example: 1659218906.
             */
            class Time : public MultiFormatter
            {
            protected:
                /**
                 * @brief Time Internal Formatter object.
                 * 
                 * This is an abstract class which is used to create all the specialized (childs) formatters needed in the Time.
                 */
                class InternalFormatter : public Formatter
                {
                protected:
                    /**
                     * @brief Pointer to the time data in epoch milliseconds.
                     */
                    std::chrono::milliseconds *_time_ms = nullptr;

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
                     * @param time_ms Pointer to the time data in epoch milliseconds.
                     */
                    InternalFormatter(const std::string &type, const std::string &key, std::chrono::milliseconds *time_ms);
                };

                /**
                 * @brief Hours Formatter object.
                 * 
                 * This class objective is to format a log message with the hours from which the log was created.
                 */
                class Hours : public InternalFormatter
                {
                protected:
                    /**
                     * @brief Gets the hours from the time data formatted as a string with 2 digits.
                     * 
                     * @return std::string Formatted hours.
                     */
                    std::string _get_hours();

                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is meant to be overritten and design to include all the needed methods to format the log message.
                     * 
                     * @return std::string Formatted hours.
                     */
                    virtual std::string _format() override;
                
                public:
                    /**
                     * @brief Construct a new Hours object.
                     */
                    Hours();
                    
                    /**
                     * @brief Construct a new Hours object.
                     * 
                     * @param key Formatting key.
                     * @param time_ms Pointer to the time data in epoch milliseconds.
                     */
                    Hours(const std::string &key, std::chrono::milliseconds *time_ms);
                };

                /**
                 * @brief Minutes Formatter object.
                 * 
                 * This class objective is to format a log message with the minutes from which the log was created.
                 */
                class Minutes : public InternalFormatter
                {
                protected:
                    /**
                     * @brief Gets the minutes from the time data formatted as a string with 2 digits.
                     * 
                     * @return std::string Formatted minutes.
                     */
                    std::string _get_minutes();

                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is meant to be overritten and design to include all the needed methods to format the log message.
                     * 
                     * @return std::string Formatted minutes.
                     */
                    virtual std::string _format() override;
                
                public:
                    /**
                     * @brief Construct a new Minutes object.
                     */
                    Minutes();

                    /**
                     * @brief Construct a new Minutes object.
                     * 
                     * @param key Formatting key.
                     * @param time_ms Pointer to the time data in epoch milliseconds.
                     */
                    Minutes(const std::string &key, std::chrono::milliseconds *time_ms);
                };

                /**
                 * @brief Seconds Formatter object.
                 * 
                 * This class objective is to format a log message with the seconds from which the log was created.
                 */
                class Seconds : public InternalFormatter
                {
                protected:
                    /**
                     * @brief Gets the seconds from the time data formatted as a string with 2 digits.
                     * 
                     * @return std::string Formatted seconds.
                     */
                    std::string _get_seconds();

                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is meant to be overritten and design to include all the needed methods to format the log message.
                     * 
                     * @return std::string Formatted seconds.
                     */
                    virtual std::string _format() override;

                public:
                    /**
                     * @brief Construct a new Seconds object.
                     */
                    Seconds();

                    /**
                     * @brief Construct a new Seconds object.
                     * 
                     * @param key Formatting key.
                     * @param time_ms Pointer to the time data in epoch milliseconds.
                     */
                    Seconds(const std::string &key, std::chrono::milliseconds *time_ms);
                };

                /**
                 * @brief Milliseconds Formatter object.
                 * 
                 * This class objective is to format a log message with the milliseconds from which the log was created.
                 */
                class Milliseconds : public InternalFormatter
                {
                protected:
                    /**
                     * @brief Gets the milliseconds from the time data formatted as a string with 3 digits.
                     * 
                     * @return std::string Formatted milliseconds.
                     */
                    std::string _get_milliseconds();

                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is meant to be overritten and design to include all the needed methods to format the log message.
                     * 
                     * @return std::string Formatted milliseconds.
                     */
                    virtual std::string _format() override;
                
                public:
                    /**
                     * @brief Construct a new Milliseconds object.
                     */
                    Milliseconds();

                    /**
                     * @brief Construct a new Milliseconds object.
                     * 
                     * @param key Formatting key.
                     * @param time_ms Pointer to the time data in epoch milliseconds.
                     */
                    Milliseconds(const std::string &key, std::chrono::milliseconds *time_ms);
                };

                /**
                 * @brief Epoch Formatter object.
                 * 
                 * This class objective is to format a log message with the epoch from which the log was created.
                 */
                class Epoch : public InternalFormatter
                {
                protected:
                    /**
                     * @brief Gets the epoch from the time data formatted as a string with 10 digits.
                     * 
                     * @return std::string Formatted epoch.
                     */
                    std::string _get_epoch();

                    /**
                     * @brief Abstract method to format the log message.
                     * 
                     * This method is meant to be overritten and design to include all the needed methods to format the log message.
                     * 
                     * @return std::string Formatted epoch.
                     */
                    virtual std::string _format() override;
                
                public:
                    /**
                     * @brief Construct a new Epoch object.
                     */
                    Epoch();

                    /**
                     * @brief Construct a new Epoch object.
                     * 
                     * @param key Formatting key.
                     * @param time_ms Pointer to the time data in epoch milliseconds.
                     */
                    Epoch(const std::string &key, std::chrono::milliseconds *time_ms);
                };
            
            protected:
                /**
                 * @brief Pointer to the time data in epoch milliseconds.
                 */
                std::chrono::milliseconds *_time_ms = new std::chrono::milliseconds();
            
            public:
                /**
                 * @brief Construct a new Time object.
                 */
                Time();

                /**
                 * @brief Destroy the Time object.
                 */
                ~Time();

                /**
                 * @brief Abstract method to format the log message.
                 * 
                 * This method is not meant to be overritten unless it is necessary to perform some extra steps before the actual formatting. If so, this function should be overritten and its additional behaviour inserted, finalizing with calling of the abstract function.
                 * 
                 * In the current case, the additional behaviour is the update of the private internal member attribute: Pointer to the time data in epoch milliseconds.
                 * 
                 * This function does not output the formatted log message. The log message is given as a reference instead, which allows its formatting on the given string.
                 */
                virtual void format(std::string &message) override;
            };
        }
    }
}
