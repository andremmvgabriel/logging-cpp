#pragma once

#include <gabe/logging/core/Sink.hpp>
#include <gabe/logging/handlers/Handler.hpp>

namespace gabe {
    namespace logging {
        namespace handlers {
            class ConsoleStdOutHandler : public Handler
            {
            public:
                ConsoleStdOutHandler();

                virtual bool evaluate(core::Sink *sink, const std::string &message) override;
            };
        }
    }
}

