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

                class Hours : public InternalFormatter
                {
                protected:
                    std::string _get_hours();
                
                public:
                    Hours();
                    Hours(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };

                class Minutes : public InternalFormatter
                {
                protected:
                    std::string _get_minutes();
                
                public:
                    Minutes();
                    Minutes(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };

                class Seconds : public InternalFormatter
                {
                protected:
                    std::string _get_seconds();
                
                public:
                    Seconds();
                    Seconds(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };

                class Milliseconds : public InternalFormatter
                {
                protected:
                    std::string _get_milliseconds();
                
                public:
                    Milliseconds();
                    Milliseconds(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };

                class Epoch : public InternalFormatter
                {
                protected:
                    std::string _get_epoch();
                
                public:
                    Epoch();
                    Epoch(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };
            
            protected:
                std::chrono::milliseconds *_time_ms = new std::chrono::milliseconds();
            
            public:
                Time();
                ~Time();

                virtual void format(std::string &message) override;
            };
        }
    }
}
