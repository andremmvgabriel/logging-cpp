#pragma once

#include <string>

#include <gabe/logging/formatters/Formatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            class MultiFormatter : public Formatter
            {
            protected:
                std::string _layout;
            
            public:
                MultiFormatter();
                MultiFormatter(const std::string &type, const std::string &key);
                MultiFormatter(const std::string &type, const std::string &key, const std::string &layout);

                std::string layout() const;
            };
        }
    }
}
