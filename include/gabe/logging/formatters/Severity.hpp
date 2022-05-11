#include <unordered_map>

#include <gabe/logging/SeverityLevel.hpp>
#include <gabe/logging/formatters/Formatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            class Severity : public Formatter
            {
            protected:
                std::unordered_map<SeverityLevel, std::string> _formatting = {
                    { SeverityLevel::TRACE,   "TRACE" },
                    { SeverityLevel::DEBUG,   "DEBUG" },
                    { SeverityLevel::INFO,    "INFO" },
                    { SeverityLevel::WARNING, "WARNING" },
                    { SeverityLevel::ERROR,   "ERROR" },
                    { SeverityLevel::FATAL,   "FATAL" }
                };

                virtual std::string _format();
            
            public:
                Severity();
            };
        }
    }
}