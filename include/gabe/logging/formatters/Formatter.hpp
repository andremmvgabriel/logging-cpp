#pragma once

#include <string>

namespace gabe {
    namespace logging {
        namespace formatters {
            /**
             * @brief Abstract Formatter object.
             * 
             * Every formatter object created should be extended from this class (or from a child that is extended already from this class).
             */
            class Formatter
            {            
            protected:
                /**
                 * @brief Formatter type/name.
                 */
                std::string _type;

                /**
                 * @brief Formatting key.
                 */
                std::string _key;
            
            protected:
                /**
                 * @brief Abstract method to format the log message.
                 * 
                 * This method is meant to be overritten and design to include all the needed methods to format the log message.
                 * 
                 * @return std::string Formatted output.
                 */
                virtual std::string _format();
            
            public:
                /**
                 * @brief Construct a new Formatter object.
                 */
                Formatter();

                /**
                 * @brief Construct a new Formatter object.
                 * 
                 * @param type Formatter type/name.
                 */
                Formatter(const std::string &type);

                /**
                 * @brief Construct a new Formatter object.
                 * 
                 * @param type Formatter type/name.
                 * @param key Formatting key.
                 */
                Formatter(const std::string &type, const std::string &key);

                /**
                 * @brief Get the type/name of the Formatter.
                 * 
                 * @return std::string Formatter type/name.
                 */
                std::string type() const;

                /**
                 * @brief Get the formatting key of the Formatter.
                 * 
                 * @return std::string Formatting key.
                 */
                std::string key() const;

                /**
                 * @brief Abstract method to format the log message.
                 * 
                 * This method is not meant to be overritten unless it is necessary to perform some extra steps before the actual formatting. If so, this function should be overritten and its additional behaviour inserted, finalizing with calling of the abstract function.
                 * 
                 * This function does not output the formatted log message. The log message is given as a reference instead, which allows its formatting on the given string.
                 */
                virtual void format(std::string &message);
            };
        }
    }
}
