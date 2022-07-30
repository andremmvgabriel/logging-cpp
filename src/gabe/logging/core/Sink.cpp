#include <gabe/logging/core/Sink.hpp>

#include <filesystem>

gabe::logging::core::Sink::Sink() : _file_directory(""), _file_name("log.txt") {
    // Creates the buffer with the desired size
    _buffer = new char[_buffer_size];

    // Opens the log file if it already exists in the system
    if (std::filesystem::exists(get_file_full_path())) {
        open_file();
    }
}

gabe::logging::core::Sink::Sink(const std::string &file_directory, const std::string &file_name) : _file_directory(file_directory), _file_name(file_name) {
    // Creates the buffer with the desired size
    _buffer = new char[_buffer_size];

    // Opens the log file if it already exists in the system
    if (std::filesystem::exists(get_file_full_path())) {
        open_file();
    }
}

gabe::logging::core::Sink::~Sink() {
    close_file();

    // Makes sure the buffer is deleted and assigned to nullptr
    if (_buffer) delete _buffer;
    _buffer = nullptr;
}

void gabe::logging::core::Sink::open_file() {
    // Safety check
    if (_file.is_open()) return;

    // Opens the log file in write only mode
    _file = std::ofstream(
        get_file_full_path(),
        std::ios::out | std::ios::app
    );
}

void gabe::logging::core::Sink::close_file() {
    // Safety check
    if (!_file.is_open()) return;

    // Closes the file
    _file.close();
}

void gabe::logging::core::Sink::sink_in(const std::string &message) {
    // Safety check
    if (should_flush(message)) return;

    // Adds the message content into the buffer
    memcpy(&_buffer[_buffer_pos], message.data(), message.size());

    // Updates the buffer writing position pointer
    _buffer_pos += message.size();
}

void gabe::logging::core::Sink::flush() {
    // Makes sure the file is opened
    open_file();

    // Writes the buffer data into the log file
    _file.write(_buffer, _buffer_pos);

    // Restarts the buffer writing position pointer
    _buffer_pos = 0;
}

bool gabe::logging::core::Sink::should_flush(const std::string &message) {
    if (_buffer_pos + message.size() > _buffer_size) return true;
    return false;
}

void gabe::logging::core::Sink::rotate_file(const std::string &new_name) {
    // Makes sure that every data from the buffer is inserted into the log file
    flush();
    close_file();

    // Creates the full path to the new log file
    std::string new_full_path = std::filesystem::path(get_file_directory()) / new_name;

    // Renames it
    std::rename(get_file_full_path().c_str(), new_full_path.c_str());
}

uint32_t gabe::logging::core::Sink::file_size() {
    // This has to be done like this. Otherwise the tellp function would return the maximum size of the file.
    if (_file.is_open())
        return _file.tellp();
    else
        return 0;
}

uint32_t gabe::logging::core::Sink::buffer_size() {
    return _buffer_pos;
}

uint32_t gabe::logging::core::Sink::buffer_max_size() {
    return _buffer_size;
}

void gabe::logging::core::Sink::set_file_name(const std::string &name) {
    // Moves the log file is it is already opened (logged into)
    if (_file.is_open()) {
        close_file();
        
        // Caches the old name and the new one
        std::string old_name = get_file_full_path();
        _file_name = name;
        std::string new_name = get_file_full_path();

        // Renames the file (moving it)
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
    // Moves the log file is it is already opened (logged into)
    if (_file.is_open()) {
        close_file();
        
        // Caches the old name and the new one
        std::string old_name = get_file_full_path();
        _file_directory = directory;
        std::string new_name = get_file_full_path();

        // Renames the file (moving it)
        rename(old_name.data(), new_name.data());
        
        open_file();
    } else {
        _file_directory = directory;
    }
}

std::string gabe::logging::core::Sink::get_file_directory() {
    return std::filesystem::absolute(_file_directory);
}

std::string gabe::logging::core::Sink::get_file_full_path() {
    return std::filesystem::absolute(_file_directory) / _file_name;
}
