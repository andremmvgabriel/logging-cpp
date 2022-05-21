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
                std::ofstream _file;
                std::string _file_name;

                char *_buffer = nullptr;
                uint32_t _buffer_size = 500000;
                uint32_t _buffer_pos = 0;
            
            protected:
                void _open_file();
                void _close_file();
            
            public:
                Sink();
                Sink(const std::string &file_path);
                ~Sink();

                void sink_in(const std::string &message);
                void flush();
                bool should_flush(const std::string &message);
            };
        }
    }
}
