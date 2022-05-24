#include <gabe/logging/core/Sink.hpp>

gabe::logging::core::Sink::Sink() {}

gabe::logging::core::Sink::Sink(const std::string &file_path) : _file_name(file_path) {
    open_file();
    _buffer = new char[_buffer_size];
}

gabe::logging::core::Sink::~Sink() {
    close_file();
    if (_buffer) delete _buffer;
    _buffer = nullptr;
}

void gabe::logging::core::Sink::open_file() {
    if (_file.is_open()) return;

    _file = std::ofstream(
        _file_name,
        std::ios::out | std::ios::app
    );
}

void gabe::logging::core::Sink::close_file() {
    if (!_file.is_open()) return;

    _file.close();
}

void gabe::logging::core::Sink::sink_in(const std::string &message) {
    // Safety check
    if (should_flush(message)) return;

    memcpy(&_buffer[_buffer_pos], message.data(), message.size());

    _buffer_pos += message.size();
}

void gabe::logging::core::Sink::flush() {
    _file.write(_buffer, _buffer_pos);
    _buffer_pos = 0;
}

bool gabe::logging::core::Sink::should_flush(const std::string &message) {
    if (_buffer_pos + message.size() > _buffer_size) return true;
    return false;
}

uint32_t gabe::logging::core::Sink::file_size() {
    return _file.tellp();
}

uint32_t gabe::logging::core::Sink::buffer_size() {
    return _buffer_pos;
}

uint32_t gabe::logging::core::Sink::buffer_max_size() {
    return _buffer_size;
}

std::string gabe::logging::core::Sink::file_name() {
    return _file_name;
}

std::string gabe::logging::core::Sink::file_path() {
    return _file_path;
}
