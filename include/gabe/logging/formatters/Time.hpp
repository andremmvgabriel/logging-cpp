#pragma once

#include <chrono>
#include <unordered_map>

#include <gabe/logging/formatters/MultiFormatter.hpp>

namespace gabe {
    namespace logging {
        namespace formatters {
            class Time : public MultiFormatter
            {
            protected:
                class InternalFormatter : public Formatter
                {
                protected:
                    std::chrono::milliseconds *_time_ms = nullptr;

                public:
                    InternalFormatter();
                    InternalFormatter(const std::string &type, const std::string &key, std::chrono::milliseconds *time_ms);
                };

                class Clock : public InternalFormatter
                {
                protected:
                    std::string _get_clock();
                    std::string _get_clock_ms();
                
                public:
                    Clock();
                    Clock(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };

                class Epoch : public InternalFormatter
                {
                protected:
                    std::string _get_epoch();
                    std::string _get_epoch_ms();
                
                public:
                    Epoch();
                    Epoch(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };
            
            protected:
                std::chrono::milliseconds *_time_ms = new std::chrono::milliseconds();

                Clock _clock = Clock("%clock", _time_ms);
                Clock _clock_ms = Clock("%msclock", _time_ms);
                Epoch _epoch = Epoch("%epoch", _time_ms);
                Epoch _epoch_ms = Epoch("%msepoch", _time_ms);

            protected:
                virtual std::string _format() override;
            
            public:
                Time();
                Time(const std::string &layout);

                ~Time();
            };
        }
    }
}
