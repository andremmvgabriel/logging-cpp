#pragma once

#include <string>

namespace gabe {
    namespace logging {
        namespace formatters {
            class Formatter
            {
            public:
                enum class Placement {
                    BEGINNING,
                    END
                };
            
            protected:
                std::string _type;
                Formatter::Placement _placement = Formatter::Placement::BEGINNING;
            
            public:
                Formatter();
                Formatter(const std::string &type);
                Formatter(const std::string &type, const Formatter::Placement &placement);

                std::string type() const;

                void set_placement(const Formatter::Placement &placement);
                Formatter::Placement get_placement() const;

                virtual void format(std::string &message);
            };
        }
    }
}
