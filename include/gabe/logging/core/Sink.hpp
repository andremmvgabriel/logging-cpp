#pragma once

#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <stdint.h>

namespace gabe {
    namespace logging {
        namespace core {
            class Sink
            {
            protected:
                char *_buffer = nullptr;
                uint32_t _buffer_size = 50;
                uint32_t _buffer_pos = 0;
            
            public:
                Sink();
                ~Sink();
                void sink_in(const std::string &message);
                void flush(std::ofstream &file);
                bool should_flush(const std::string &message);
            };
        }
    }
}
