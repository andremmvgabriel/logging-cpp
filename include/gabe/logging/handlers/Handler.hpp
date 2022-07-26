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

                virtual void check_sink(core::Sink *sink);
                virtual bool evaluate(core::Sink *sink, const std::string &message);
                virtual std::string create_handled_file_name(const std::string &file_name);
            };
        }
    }
}
