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
                std::string _file_directory;

                char *_buffer = nullptr;
                uint32_t _buffer_size = 500000;
                uint32_t _buffer_pos = 0;
            
            public:
                Sink();
                Sink(const std::string &file_directory, const std::string &file_name);
                ~Sink();

                void open_file();
                void close_file();

                void sink_in(const std::string &message);
                void flush();
                bool should_flush(const std::string &message);

                void rotate_file(const std::string &new_name);

                uint32_t file_size();
                uint32_t buffer_size();
                uint32_t buffer_max_size();

                void set_file_name(const std::string &name);
                std::string get_file_name();

                void set_file_directory(const std::string &directory);
                std::string get_file_directory();

                std::string get_file_full_path();
            };
        }
    }
}
