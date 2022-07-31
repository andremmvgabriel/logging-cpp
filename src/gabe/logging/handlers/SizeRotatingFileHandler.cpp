#include <gabe/logging/handlers/SizeRotatingFileHandler.hpp>

#include <filesystem>
#include <fmt/format.h>

gabe::logging::handlers::SizeRotatingFileHandler::SizeRotatingFileHandler() : Handler("SizeRotatingFileHandler"), _size(5000000) {}

gabe::logging::handlers::SizeRotatingFileHandler::SizeRotatingFileHandler(uint64_t size) : Handler("SizeRotatingFileHandler"), _size(size) {}

std::string gabe::logging::handlers::SizeRotatingFileHandler::_find_last_and_get_after(const std::string &target, const std::string &key) {
    // Checks the position of the given key in the given target string.
    std::size_t position = target.find_last_of(key);

    // Gets the string sub part after the key, if existent
    if (position != -1) return std::string(&target[position + 1]);

    // Returns the given target, since the key is not present
    return target;
}

std::vector<std::string> gabe::logging::handlers::SizeRotatingFileHandler::_find_log_files(const std::string &directory, const std::string &file_name) {
    // List of files that will be outputted
    std::vector<std::string> files;

    // Gets the filename (without extension)
    std::string file_stem = std::filesystem::path(file_name).stem();

    // Search for log files in the directory
    for (const auto &entry : std::filesystem::directory_iterator(directory)) {
        std::string name = entry.path().stem();

        if (name.find(file_stem) != -1) {
            files.push_back(name);
        }
    }

    return files;
}

void gabe::logging::handlers::SizeRotatingFileHandler::_update_files_counter(const std::vector<std::string> &log_files) {
    int files_counter = -1;

    for (std::string file : log_files) {
        // Gets the counter segment of the file name
        std::string counter_str = _find_last_and_get_after(file, ".");

        try {
            // Converts to integer
            int counter = std::stoi(counter_str);

            // Updates the counter
            if (files_counter < counter) files_counter = counter;
        }
        catch(const std::exception& e) { continue; }
    }

    // Increases the counter to start format new logging files
    _files_counter = ++files_counter;
}

void gabe::logging::handlers::SizeRotatingFileHandler::check_sink(core::Sink *sink) {
    // Gets the list of log files in the log files directory
    std::vector<std::string> log_files = _find_log_files(sink->get_file_directory(), sink->get_file_name());

    // Analyses the log files and updates the files counter
    _update_files_counter(log_files);
}

bool gabe::logging::handlers::SizeRotatingFileHandler::evaluate(core::Sink *sink, const std::string &message) {
    // Gets the total size in the log file + buffer sink
    uint64_t total_size = sink->file_size() + sink->buffer_size();

    // Returns true if this size exceeds the maximum size of the file
    if (total_size >= _size)
        return true;
    
    return false;
}

std::string gabe::logging::handlers::SizeRotatingFileHandler::create_handled_file_name(const std::string &file_name) {
    std::filesystem::path name(file_name);

    // Creates the new name
    return std::string(name.stem()) + "." + fmt::format("{:06d}", _files_counter++) + std::string(name.extension());
}
