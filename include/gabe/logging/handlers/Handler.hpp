#pragma once

#include <string>

#include <gabe/logging/core/Sink.hpp>

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
                
                std::string type() const;

                virtual bool evaluate();
                virtual void handle(core::Sink *sink, const std::string &message);
            };
        }
    }
}
