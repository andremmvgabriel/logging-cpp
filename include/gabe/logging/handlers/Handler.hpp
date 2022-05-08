#pragma once

#include <string>

namespace gabe {
    namespace logging {
        namespace handlers {
            class Handler
            {
            protected:
                std::string _type;

            public:
                Handler();
                Handler(const std::string &type);
                
                std::string type();
                virtual bool evaluate();
                virtual void handle();
            };
        }
    }
}
