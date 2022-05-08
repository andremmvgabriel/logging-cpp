#pragma once

#include <unordered_map>

#include <gabe/logging/formatters/Formatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            class Time : public Formatter
            {
            public:
                enum class Layout {
                    CLOCK,
                    CLOCK_MS,
                    EPOCH,
                    EPOCH_MS
                };
            
            protected:
                Layout _layout = Layout::CLOCK_MS;

                std::unordered_map<Layout, std::string (Time::*) ()> _format_methods = {
                    {   Layout::CLOCK,      &Time::_clock       },
                    {   Layout::CLOCK_MS,   &Time::_clock_ms    },
                    {   Layout::EPOCH,      &Time::_epoch       },
                    {   Layout::EPOCH_MS,   &Time::_epoch_ms    }
                };

                std::string _clock();
                std::string _clock_ms();
                std::string _epoch();
                std::string _epoch_ms();
            
            public:
                Time();
                Time(const Formatter::Placement &placement, const Layout &layout = Layout::CLOCK_MS);

                void set_layout(const Layout &layout);

                virtual void format(std::string &message);
            };
        }
    }
}
