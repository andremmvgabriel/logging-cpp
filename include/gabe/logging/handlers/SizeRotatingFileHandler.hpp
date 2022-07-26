#pragma once

#include <vector>
#include <string>

#include <gabe/logging/core/Sink.hpp>
#include <gabe/logging/handlers/Handler.hpp>

namespace gabe {
    namespace logging {
        namespace handlers {
            class SizeRotatingFileHandler : public Handler
            {
            protected:
                uint64_t _size;
                uint16_t _files_counter = 0;
            
            protected:
                std::string _find_last_and_get_after(const std::string &target, const std::string &key);

                std::vector<std::string> _find_log_files(const std::string &directory, const std::string &file_name);

                void _update_files_counter(const std::vector<std::string> &log_files);

                void _rotate_file(core::Sink *sink);

            public:
                SizeRotatingFileHandler();
                SizeRotatingFileHandler(uint64_t size);

                virtual void check_sink(core::Sink *sink) override;
                virtual void handle(core::Sink *sink, const std::string &message) override;
            };
        }
    }
}
