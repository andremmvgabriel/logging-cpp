#pragma once

#include <string>
#include <vector>

#include <gabe/logging/formatters/Formatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            /**
             * @brief Abstract MultiFormatter object.
             * 
             * This class is extended from the abstract class Formatter. However, this is considered to be an abstract one as well due to its specialization as a formatter with multi formattings.
             * 
             * As so, every multi formatter object created should extend from this class.
             */
            class MultiFormatter : public Formatter
            {
            protected:
                /**
                 * @brief List of the multiple formatter objects.
                 */
                std::vector<Formatter*> _formatters;

            public:
                /**
                 * @brief Construct a new Multi Formatter object.
                 */
                MultiFormatter();

                /**
                 * @brief Construct a new Multi Formatter object.
                 * 
                 * @param type Formatter type/name.
                 */
                MultiFormatter(const std::string &type);

                /**
                 * @brief Destroy the Multi Formatter object.
                 * 
                 * This method ensures that all the created formatter pointers are correctly deleted/freed.
                 */
                ~MultiFormatter();

                /**
                 * @brief Abstract method to format the log message.
                 * 
                 * This method is not meant to be overritten unless it is necessary to perform some extra steps before the actual formatting. If so, this function should be overritten and its additional behaviour inserted, finalizing with calling of the abstract function.
                 * 
                 * This function does not output the formatted log message. The log message is given as a reference instead, which allows its formatting on the given string.
                 */
                virtual void format(std::string &message) override;

                /**
                 * @brief Adds a log formatter to the multi formatter object.
                 * 
                 * Adds a log formatter object into the multi formatter object. This formatter must be a child of the Formatter abstract object.
                 * 
                 * @tparam FormatterT Formatter type.
                 * @param formatter Formatter object.
                 */
                template<typename FormatterT>
                void add_formatter(const FormatterT &formatter) {
                    // Creates a new pointer of the formatter type and which will copy the object of the given formatter.
                    FormatterT* formatter_copy = new FormatterT();
                    *formatter_copy = formatter;

                    // Adds the formatter to the list
                    _formatters.push_back(dynamic_cast<formatters::Formatter*>(formatter_copy));
                }
            };
        }
    }
}
