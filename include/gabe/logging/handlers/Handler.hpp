#pragma once

#include <string>

#include <gabe/logging/core/Sink.hpp>

namespace gabe {
    namespace logging {
        namespace handlers {
            /**
             * @brief Abstract Handler object.
             * 
             * Every handler object created should be extended from this class (or from a child that is extended already from this class).
             */
            class Handler
            {
            protected:
                /**
                 * @brief Handler type/name.
                 */
                std::string _type;

            public:
                /**
                 * @brief Construct a new Handler object.
                 */
                Handler();

                /**
                 * @brief Construct a new Handler object.
                 * 
                 * @param type Handler type/name.
                 */
                Handler(const std::string &type);
                
                /**
                 * @brief Get the type/name of the Handler.
                 * 
                 * @return std::string Handler type/name.
                 */
                std::string type() const;

                /**
                 * @brief Evaluates a given logger sink to update internal management variables.
                 * 
                 * This method is abstract and is designed to be overritten by a child class. It's behaviour should be written accordingly to child class needs to update its internal management variables.
                 * 
                 * @param sink Pointer to the logger sink.
                 */
                virtual void check_sink(core::Sink *sink);

                /**
                 * @brief Evaluates if the logger log file needs to be managed by the handler.
                 * 
                 * This method is abstract and is designed to be overritten by a child class. It's behaviour should be written accordingly to child class needs to confirm is the file should or not should be handled at the calling moment. 
                 * 
                 * @param sink Pointer to the logger sink.
                 * @param message Log message.
                 * @return bool Should/Shouldn't manage log file.
                 */
                virtual bool evaluate(core::Sink *sink, const std::string &message);

                /**
                 * @brief Creates a new file name for the logger file.
                 * 
                 * This method is abstract and is designed to be overritten by a child class. It's behaviour should be written accordingly to child class needs to rename the logger log file. 
                 * 
                 * @param file_name Current log file name.
                 * @return std::string Handled log file name.
                 */
                virtual std::string create_handled_file_name(const std::string &file_name);
            };
        }
    }
}
