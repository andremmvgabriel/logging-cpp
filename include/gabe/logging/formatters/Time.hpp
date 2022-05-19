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

                class Hours : public InternalFormatter
                {
                protected:
                    std::string _get_hours();
                
                public:
                    Hours();
                    Hours(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };

                class Minutes : public InternalFormatter
                {
                protected:
                    std::string _get_minutes();
                
                public:
                    Minutes();
                    Minutes(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };

                class Seconds : public InternalFormatter
                {
                protected:
                    std::string _get_seconds();
                
                public:
                    Seconds();
                    Seconds(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };

                class Milliseconds : public InternalFormatter
                {
                protected:
                    std::string _get_milliseconds();
                
                public:
                    Milliseconds();
                    Milliseconds(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };

                class Epoch : public InternalFormatter
                {
                protected:
                    std::string _get_epoch();
                
                public:
                    Epoch();
                    Epoch(const std::string &key, std::chrono::milliseconds *time_ms);

                    virtual std::string _format() override;
                };
            
            protected:
                std::chrono::milliseconds *_time_ms = new std::chrono::milliseconds();

                Hours _hours = Hours("%hour", _time_ms);
                Minutes _minutes = Minutes("%min", _time_ms);
                Seconds _seconds = Seconds("%sec", _time_ms);
                Milliseconds _milliseconds = Milliseconds("%ms", _time_ms);
                Epoch _epoch = Epoch("%epoch", _time_ms);
            
            public:
                Time();
                Time(const std::string &layout);

                ~Time();

                virtual void format(std::string &message);
            };
        }
    }
}
