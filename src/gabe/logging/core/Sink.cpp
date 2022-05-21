#include <gabe/logging/core/Sink.hpp>

gabe::logging::core::Sink::Sink() {}

gabe::logging::core::Sink::Sink(const std::string &file_path) : _file_name(file_path) {
    _open_file();
    _buffer = new char[_buffer_size];
}

gabe::logging::core::Sink::~Sink() {
    _close_file();
    if (_buffer) delete _buffer;
    _buffer = nullptr;
}

void gabe::logging::core::Sink::_open_file() {
    if (_file.is_open()) return;

    _file = std::ofstream(
        _file_name,
        std::ios::out | std::ios::app
    );
}

void gabe::logging::core::Sink::_close_file() {
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