#pragma once

#include <ctime>
#include <unordered_map>
#include <gabe/logging/handlers/Handler.hpp>

namespace gabe {
    namespace logging {
        namespace handlers {
            class TimeRotatingFileHandler : public Handler
            {
            public:
                enum class Rotation {
                    MINUTE  =   1,
                    HOUR    =   2,
                    DAY     =   4,
                    WEEK    =   8,
                    MONTH   =   16
                };
            
            protected:
                bool _minute_evaluation(const std::tm &time_calendar);
                bool _hour_evaluation(const std::tm &time_calendar);
                bool _day_evaluation(const std::tm &time_calendar);
                bool _week_evaluation(const std::tm &time_calendar);
                bool _month_evaluation(const std::tm &time_calendar);
            
            public:
                std::time_t _time_epoch;
                std::tm _time_calendar;
                Rotation _rotation = Rotation::DAY;

                std::unordered_map<Rotation, bool (TimeRotatingFileHandler::*) (const std::tm &)> _evaluation_methods = {
                    {   Rotation::MINUTE,   &TimeRotatingFileHandler::_minute_evaluation   },
                    {   Rotation::HOUR,     &TimeRotatingFileHandler::_hour_evaluation     },
                    {   Rotation::DAY,      &TimeRotatingFileHandler::_day_evaluation      },
                    {   Rotation::WEEK,     &TimeRotatingFileHandler::_week_evaluation     },
                    {   Rotation::MONTH,    &TimeRotatingFileHandler::_month_evaluation    }
                };
            
            public:
                TimeRotatingFileHandler();
                TimeRotatingFileHandler(const Rotation &rotation);

                virtual bool evaluate() override;
                virtual void handle() override;
            };
        }
    }
}
