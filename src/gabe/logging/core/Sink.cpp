#include <gabe/logging/core/Sink.hpp>

#include <filesystem>

gabe::logging::core::Sink::Sink() : _file_directory(""), _file_name("log.txt") {
    _buffer = new char[_buffer_size];
}

gabe::logging::core::Sink::Sink(const std::string &file_directory, const std::string &file_name) : _file_directory(file_directory), _file_name(file_name) {
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
        get_file_full_path(),
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
    open_file();
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

void gabe::logging::core::Sink::set_file_name(const std::string &name) {
    if (_file.is_open()) {
        close_file();
        
        // Caches the old name and the new one
        std::string old_name = get_file_full_path();
        _file_name = name;
        std::string new_name = get_file_full_path();

        rename(old_name.data(), new_name.data());
        open_file();
    } else {
        _file_name = name;
    }
}

std::string gabe::logging::core::Sink::get_file_name() {
    return _file_name;
}

void gabe::logging::core::Sink::set_file_directory(const std::string &directory) {
    if (_file.is_open()) {
        close_file();
        
        // Caches the old name and the new one
        std::string old_name = get_file_full_path();
        _file_directory = directory;
        std::string new_name = get_file_full_path();

        rename(old_name.data(), new_name.data());
        open_file();
    } else {
        _file_directory = directory;
    }
}

std::string gabe::logging::core::Sink::get_file_directory() {
    return _file_directory;
}

std::string gabe::logging::core::Sink::get_file_full_path() {
    return std::filesystem::absolute(_file_directory) / _file_name;
}
