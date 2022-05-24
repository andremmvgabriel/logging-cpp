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
            
            protected:
                virtual void _evaluate();

            public:
                Handler();
                Handler(const std::string &type);
                
                std::string type() const;

                virtual void check_sink(core::Sink *sink);
                virtual void handle(core::Sink *sink, const std::string &message);
            };
        }
    }
}
