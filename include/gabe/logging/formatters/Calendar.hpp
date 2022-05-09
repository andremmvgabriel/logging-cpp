#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <unordered_map>

#include <gabe/logging/formatters/Formatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            class Calendar : public Formatter
            {
            public:
                enum class Layout {
                    YEAR,
                    MONTH,
                    DAY,
                    WEEK
                };

                std::string _months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dec"};

                std::string _week_days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

                std::string _get_year(const std::tm &calendar);
                std::string _get_month(const std::tm &calendar);
                std::string _get_day(const std::tm &calendar);
                std::string _get_weekday(const std::tm &calendar);
                std::string _get_calendar();
            
            protected:
                std::vector<Layout> _layout = { Layout::YEAR, Layout::MONTH, Layout::DAY };
                Formatter::Placement _placement = Formatter::Placement::BEGINNING;

                std::unordered_map<Layout, std::string (Calendar::*) (const std::tm &)> _format_methods = {
                    {   Layout::YEAR,   &Calendar::_get_year    },
                    {   Layout::MONTH,  &Calendar::_get_month   },
                    {   Layout::DAY,    &Calendar::_get_day     },
                    {   Layout::WEEK,   &Calendar::_get_weekday }
                };
            
            public:
                Calendar();
                Calendar(const Formatter::Placement &placement, const std::vector<Layout> &layout = { Layout::YEAR, Layout::MONTH, Layout::DAY } );

                void set_layout(const std::vector<Layout> &layout);

                virtual void format(std::string &message);
            };
        }
    }
}
