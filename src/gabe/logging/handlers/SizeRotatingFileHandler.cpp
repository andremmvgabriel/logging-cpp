#include <gabe/logging/handlers/SizeRotatingFileHandler.hpp>

#include <filesystem>
#include <fmt/format.h>

gabe::logging::handlers::SizeRotatingFileHandler::SizeRotatingFileHandler() : Handler("SizeRotatingFileHandler"), _size(5000000) {}

gabe::logging::handlers::SizeRotatingFileHandler::SizeRotatingFileHandler(uint64_t size) : Handler("SizeRotatingFileHandler"), _size(size) {}

std::vector<std::string> gabe::logging::handlers::SizeRotatingFileHandler::_find(std::string target, const std::string &key) {
    std::vector<std::string> parts;

    std::size_t position = target.find(key);

    while (position != -1) {
        parts.emplace_back(std::string(&target[0], &target[position]));
        target = std::string(&target[position + 1]);
        position = target.find(key);
    }

    parts.push_back(target);

    return parts;
}

std::string gabe::logging::handlers::SizeRotatingFileHandler::_find_and_get_before(const std::string &target, const std::string &key, bool last) {
    std::size_t position = last ? target.find_last_of(key) : target.find_first_of(key);

    if (position != -1) return std::string(&target[0], &target[position]);

    return target;
}

std::string gabe::logging::handlers::SizeRotatingFileHandler::_find_and_get_after(const std::string &target, const std::string &key, bool last) {
    std::size_t position = last ? target.find_last_of(key) : target.find_first_of(key);

    if (position != -1) return std::string(&target[position + 1]);

    return target;
}

std::string gabe::logging::handlers::SizeRotatingFileHandler::_find_last_and_get_after(const std::string &target, const std::string &key) {
    std::size_t position = target.find_last_of(key);

    if (position != -1) return std::string(&target[position + 1]);

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

void gabe::logging::handlers::SizeRotatingFileHandler::_rotate_file(core::Sink *sink) {
    std::filesystem::path file_path(sink->get_file_directory());
    std::filesystem::path file_name(sink->get_file_name());

    // Creates the new name
    std::string new_name = std::string(file_path / file_name.stem()) + "." + fmt::format("{:06d}", _files_counter++) + std::string(file_name.extension());

    std::rename(sink->get_file_full_path().c_str(), new_name.c_str());
}

void gabe::logging::handlers::SizeRotatingFileHandler::check_sink(core::Sink *sink) {
    std::vector<std::string> log_files = _find_log_files(sink->get_file_directory(), sink->get_file_name());

    _update_files_counter(log_files);
}

void gabe::logging::handlers::SizeRotatingFileHandler::handle(core::Sink *sink, const std::string &message) {
    uint64_t total_size = sink->file_size() + sink->buffer_size();

    if (total_size >= _size) {
        sink->flush();
        sink->close_file();
        _rotate_file(sink);
    }
}
