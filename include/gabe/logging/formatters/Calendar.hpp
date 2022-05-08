#pragma once

#include <gabe/logging/formatters/Formatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            class Calendar : public Formatter
            {
            public:
                enum class Layout {
                    YEAR_MONTH_DAY,
                    YEAR_MONTH_DAY_WEEK,
                    MONTH_DAY,
                    MONTH_DAY_WEEK,
                    YEAR_DAY_MONTH,
                    YEAR_DAY_MONTH_WEEK,
                    DAY_MONTH,
                    DAY_MONTH_WEEK
                };

                std::string _months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dec"};
            
            protected:
                Layout _layout = Layout::YEAR_MONTH_DAY;
                Formatter::Placement _placement = Formatter::Placement::BEGINNING;
            
            public:
                virtual void format(std::string &message);
            };
        }
    }
}
