#pragma once

#include <gabe/logging/core/Sink.hpp>
#include <gabe/logging/handlers/Handler.hpp>

namespace gabe {
    namespace logging {
        namespace handlers {
            /**
             * @brief Console Standard Output handler object.
             * 
             * This class is responsible for printing every log message into a console/terminal.
             */
            class ConsoleStdOutHandler : public Handler
            {
            public:
                /**
                 * @brief Construct a new Console Std Out Handler object.
                 */
                ConsoleStdOutHandler();

                /**
                 * @brief Evaluates if the logger log file needs to be managed by the handler.
                 * 
                 * This method is abstract and is designed to be overritten by a child class. It's behaviour should be written accordingly to child class needs to confirm is the file should or not should be handled at the calling moment.
                 * 
                 * In this class, this function just prints the log message into the console/terminal, and always return false.
                 * 
                 * @param sink Pointer to the logger sink.
                 * @param message Log message.
                 * @return bool Always false.
                 */
                virtual bool evaluate(core::Sink *sink, const std::string &message) override;
            };
        }
    }
}

