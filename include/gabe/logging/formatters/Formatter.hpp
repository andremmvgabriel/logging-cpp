#pragma once

#include <string>

namespace gabe {
    namespace logging {
        namespace formatters {
            class Formatter
            {
            public:
                enum class Placement {
                    BEGINNING   =   1,
                    BEFORE_LOG  =   2,
                    AFTER_LOG   =   4,
                    END         =   8
                };
            
            public:
                virtual void format(std::string &message);
            };
        }
    }
}
