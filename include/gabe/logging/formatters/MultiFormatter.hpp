#pragma once

#include <string>
#include <vector>

#include <gabe/logging/formatters/Formatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            class MultiFormatter : public Formatter
            {
            protected:
                std::vector<Formatter*> _formatters;

            public:
                MultiFormatter();
                MultiFormatter(const std::string &type);

                ~MultiFormatter();

                virtual void format(std::string &message) override;

                template<typename FormatterT>
                void add_formatter(const FormatterT &formatter) {
                    FormatterT* formatter_copy = new FormatterT();
                    *formatter_copy = formatter;

                    _formatters.push_back(dynamic_cast<formatters::Formatter*>(formatter_copy));
                }
            };
        }
    }
}
