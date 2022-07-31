#pragma once

#include <ctime>
#include <unordered_map>
#include <gabe/logging/handlers/Handler.hpp>

namespace gabe {
    namespace logging {
        namespace handlers {
            /**
             * @brief Time Rotating File handler object.
             * 
             * This class is responsible for handling the logger log files based on time.
             */
            class TimeRotatingFileHandler : public Handler
            {            
            protected:
                /**
                 * @brief Evaluates if a minute already passed.
                 * 
                 * @param time_calendar Time data structure.
                 * @return bool Did/Didn't a minute passed.
                 */
                bool _minute_evaluation(const std::tm &time_calendar);

                /**
                 * @brief Evaluates if a hour already passed.
                 * 
                 * @param time_calendar Time data structure.
                 * @return bool Did/Didn't a hour passed.
                 */
                bool _hour_evaluation(const std::tm &time_calendar);

                /**
                 * @brief Evaluates if a day already passed.
                 * 
                 * @param time_calendar Time data structure.
                 * @return bool Did/Didn't a day passed.
                 */
                bool _day_evaluation(const std::tm &time_calendar);

                /**
                 * @brief Evaluates if a week already passed.
                 * 
                 * @param time_calendar Time data structure.
                 * @return bool Did/Didn't a week passed.
                 */
                bool _week_evaluation(const std::tm &time_calendar);

                /**
                 * @brief Evaluates if a month already passed.
                 * 
                 * @param time_calendar Time data structure.
                 * @return bool Did/Didn't a month passed.
                 */
                bool _month_evaluation(const std::tm &time_calendar);
            
            public:
                /**
                 * @brief Time since epoch in milliseconds.
                 */
                std::time_t _time_epoch;

                /**
                 * @brief Calendar data structure.
                 */
                std::tm _time_calendar;

                /**
                 * @brief Evaluation type.
                 * 
                 * M/m -> Minute evaluation;
                 * H/h -> Hour evaluation;
                 * D/d -> Day evaluation;
                 * W/w -> Week evaluation;
                 * MTH/mth -> Month evaluation.
                 */
                std::string _rotation = "D";

                /**
                 * @brief Evaluation methods mapping.
                 */
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
            
            public:
                /**
                 * @brief Construct a new Time Rotating File Handler object.
                 */
                TimeRotatingFileHandler();

                /**
                 * @brief Construct a new Time Rotating File Handler object.
                 * 
                 * @param rotation Evaluation type.
                 */
                TimeRotatingFileHandler(const std::string &rotation);

                /**
                 * @brief Evaluates a given logger sink to update internal management variables.
                 * 
                 * This method is abstract and is designed to be overritten by a child class. It's behaviour should be written accordingly to child class needs to update its internal management variables.
                 * 
                 * In this class, it checks the current logger log file date, and updates the time epoch and time calendar variables.
                 * 
                 * @param sink Pointer to the logger sink.
                 */
                virtual void check_sink(core::Sink *sink) override;

                /**
                 * @brief Evaluates if the logger log file needs to be managed by the handler.
                 * 
                 * This method is abstract and is designed to be overritten by a child class. It's behaviour should be written accordingly to child class needs to confirm is the file should or not should be handled at the calling moment.
                 * 
                 * In this class, evaluates the time of the log file based on the evaluation type given at its constructor.
                 * 
                 * @param sink Pointer to the logger sink.
                 * @param message Log message.
                 * @return bool Should/Shouldn't manage log file.
                 */
                virtual bool evaluate(core::Sink *sink, const std::string &message) override;

                /**
                 * @brief Creates a new file name for the logger file.
                 * 
                 * This method is abstract and is designed to be overritten by a child class. It's behaviour should be written accordingly to child class needs to rename the logger log file.
                 * 
                 * In this class, it returns the given log file name with the respectively time.
                 * 
                 * @param file_name Current log file name.
                 * @return std::string Handled log file name.
                 */
                virtual std::string create_handled_file_name(const std::string &file_name) override;
            };
        }
    }
}
