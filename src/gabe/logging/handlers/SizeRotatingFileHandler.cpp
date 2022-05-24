#include <gabe/logging/handlers/SizeRotatingFileHandler.hpp>

#include <filesystem>

gabe::logging::handlers::SizeRotatingFileHandler::SizeRotatingFileHandler() : _size(5000000) {}

gabe::logging::handlers::SizeRotatingFileHandler::SizeRotatingFileHandler(uint64_t size) : _size(size) {}

// void gabe::logging::handlers::SizeRotatingFileHandler::_evaluate() {
//     // #include <string>
//     // #include <iostream>
//     // #include <filesystem>
//     // namespace fs = std::filesystem;

//     // int main()
//     // {
//     //     std::string path = "/path/to/directory";
//     //     for (const auto & entry : fs::directory_iterator(path))
//     //         std::cout << entry.path() << std::endl;
//     // }
// }

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
        printf("%s\n", file_name.c_str());

        std::size_t position = file_name.find_last_of('/');

        if (position != -1) {
            file_name = std::string(&file_name[position + 1]);
        }

        position = file_name.find(file_name);

        if (position != -1) {
            files.push_back(file_name);
        }
    }

    return files;
}

void gabe::logging::handlers::SizeRotatingFileHandler::_update_files_counter(const std::vector<std::string> &log_files) {
    for (std::string file : log_files) {
        std::time_t position = file.find_last_of('.');

        if (position != -1) {
            file = std::string(&file[0], &file[position]);
        }

        position = file.find_last_of('.');

        if (position == -1) continue;

        file = std::string(&file[position + 1]);

        position = file.find('-');

        if (position != -1) continue;

        int counter = std::stoi(file);
        printf("%d\n", counter);

        if (_files_counter < counter) {
            _files_counter = counter;
        }
    }

    _files_counter++;
    printf("%d\n", _files_counter);
}

void gabe::logging::handlers::SizeRotatingFileHandler::_rotate_file(core::Sink *sink) {
    std::string old_name = sink->file_name();

    std::size_t dot_pos = old_name.find(".");

    std::string name(&old_name.data()[0], &old_name.data()[dot_pos]);
    std::string extension(&old_name.data()[dot_pos]);

    std::string new_name = name + "." + std::to_string(_files_counter++) + extension;

    rename(old_name.data(), new_name.data());
}

void gabe::logging::handlers::SizeRotatingFileHandler::check_sink(core::Sink *sink) {
    std::vector<std::string> log_files = _find_log_files(sink->file_path(), sink->file_name());

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
