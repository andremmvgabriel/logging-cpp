#include <gabe/logging/handlers/SizeRotatingFileHandler.hpp>

#include <filesystem>

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

std::vector<std::string> gabe::logging::handlers::SizeRotatingFileHandler::_find_log_files(const std::string &directory, const std::string &file_name) {
    std::vector<std::string> files;

    for (const auto &entry : std::filesystem::directory_iterator(directory)) {
        std::string file_name = entry.path();

        file_name = _find_and_get_after(file_name, "/", true);

        if (file_name.find(file_name) != -1)
            files.push_back(file_name);
    }

    return files;
}

void gabe::logging::handlers::SizeRotatingFileHandler::_update_files_counter(const std::vector<std::string> &log_files) {
    for (std::string file : log_files) {
        // Removes the extention from the filename
        file = _find_and_get_before(file, ".", true);

        // Checks if the file has been handled before
        if (file.find_last_of('.') == -1) continue;

        // Gets the formatted part by the handle 
        file = _find_and_get_after(file, ".", true);

        // Checks if the formatter part is from another handler
        if (file.find('-') != -1) continue;

        // Gets the counter 
        int counter = std::stoi(file);

        // Updates the counter
        if (_files_counter < counter) _files_counter = counter;
    }

    // Increases the counter to start format new logging files
    _files_counter++;
}

void gabe::logging::handlers::SizeRotatingFileHandler::_rotate_file(core::Sink *sink) {
    std::string new_name = sink->file_directory() + "/" + _find_and_get_before(sink->file_name(), ".") + std::to_string(_files_counter++);

    if (sink->file_name().find(".") != -1) new_name += "." + _find_and_get_after(sink->file_name(), ".");

    rename(sink->file_full_path().data(), new_name.data());
}

void gabe::logging::handlers::SizeRotatingFileHandler::check_sink(core::Sink *sink) {
    std::vector<std::string> log_files = _find_log_files(sink->file_directory(), sink->file_name());

    _update_files_counter(log_files);
}

void gabe::logging::handlers::SizeRotatingFileHandler::handle(core::Sink *sink, const std::string &message) {
    uint64_t total_size = sink->file_size() + sink->buffer_size();

    if (total_size >= _size) {
        sink->flush();
        sink->close_file();
        _rotate_file(sink);
        sink->open_file();
    }
}
