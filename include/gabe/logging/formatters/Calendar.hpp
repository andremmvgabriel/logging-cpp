#pragma once

#include <string>
#include <ctime>
#include <unordered_map>

#include <gabe/logging/formatters/MultiFormatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            class Calendar : public MultiFormatter
            {
            protected:
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

                Year _year = Year("%year", _calendar);
                Month _month = Month("%month", _calendar);
                Month _smonth = Month("%smonth", _calendar);
                Day _day = Day("%day", _calendar);
                Week _week = Week("%week", _calendar);
                Week _sweek = Week("%sweek", _calendar);
            
            protected:
                virtual std::string _format() override;
            
            public:
                Calendar();
                Calendar(const std::string &calendar_format);

                ~Calendar();
            };
        }
    }
}
