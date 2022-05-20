#pragma once

#include <string>

#include <gabe/logging/formatters/Formatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            class MultiFormatter : public Formatter
            {
            public:
                MultiFormatter();
                MultiFormatter(const std::string &type);
            };
        }
    }
}
