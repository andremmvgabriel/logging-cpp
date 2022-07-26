#pragma once

#include <ctime>
#include <unordered_map>
#include <gabe/logging/handlers/Handler.hpp>

namespace gabe {
    namespace logging {
        namespace handlers {
            class TimeRotatingFileHandler : public Handler
            {            
            protected:
                bool _minute_evaluation(const std::tm &time_calendar);
                bool _hour_evaluation(const std::tm &time_calendar);
                bool _day_evaluation(const std::tm &time_calendar);
                bool _week_evaluation(const std::tm &time_calendar);
                bool _month_evaluation(const std::tm &time_calendar);
            
            public:
                std::time_t _time_epoch;
                std::tm _time_calendar;
                std::string _rotation = "D";

                std::unordered_map<std::string, bool (TimeRotatingFileHandler::*) (const std::tm &)> _evaluation_methods = {
                    {   "m",    &TimeRotatingFileHandler::_minute_evaluation   },
                    {   "M",    &TimeRotatingFileHandler::_minute_evaluation   },
                    {   "h",    &TimeRotatingFileHandler::_hour_evaluation     },
                    {   "H",    &TimeRotatingFileHandler::_hour_evaluation     },
                    {   "d",    &TimeRotatingFileHandler::_day_evaluation      },
                    {   "D",    &TimeRotatingFileHandler::_day_evaluation      },
                    {   "w",    &TimeRotatingFileHandler::_week_evaluation     },
                    {   "W",    &TimeRotatingFileHandler::_week_evaluation     },
                    {   "mth",  &TimeRotatingFileHandler::_month_evaluation    },
                    {   "MTH",  &TimeRotatingFileHandler::_month_evaluation    }
                };
            
            protected:
                std::string _find_and_get_before(const std::string &target, const std::string &key, bool last = false);
                std::string _find_and_get_after(const std::string &target, const std::string &key, bool last = false);
            
            public:
                TimeRotatingFileHandler();
                TimeRotatingFileHandler(const std::string &rotation);

                virtual void check_sink(core::Sink *sink) override;
                virtual bool evaluate(core::Sink *sink, const std::string &message) override;
                virtual std::string create_handled_file_name(const std::string &file_name) override;
            };
        }
    }
}
