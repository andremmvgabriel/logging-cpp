#include <logging.hpp>

void gabe::logging::utils::text_alignment::left(std::string &msg, const int width) {
    // Checks if the size of the message is within the given width
    if (msg.size() <= width) {
        int final_size = width - msg.size();
        for (int i = 0; i < final_size; i++) {
            msg.push_back(' ');
        }
    }
    else {
        int remove_size = msg.size() - width - 1;
        for (int i = remove_size; i >= 0; i--) {
            msg.pop_back();
        }
    }
}

void gabe::logging::utils::text_alignment::right(std::string &msg, const int width) {
    if (msg.size() <= width) {
        int final_size = width - msg.size();
        std::string decoy;
        for (int i = 0; i < final_size; i++) {
            decoy.push_back(' ');
        }
        msg.insert(msg.begin(), decoy.begin(), decoy.end());
    }
    else {
        int remove_size = msg.size() - width - 1;
        for (int i = remove_size; i >= 0; i--) {
            msg.pop_back();
        }
    }
}

void gabe::logging::utils::text_alignment::center(std::string &msg, const int width) {
    if (msg.size() <= width) {
        int decoy1_size = (width - msg.size())/2;
        int decoy2_size = width - msg.size() - decoy1_size;
        std::string decoy1;
        for (int i = 0; i < decoy1_size; i++) { decoy1.push_back(' '); }
        msg.insert(msg.begin(), decoy1.begin(), decoy1.end());
        for (int i = 0; i < decoy2_size; i++) { msg.push_back(' '); }
    }
    else {
        int remove_size = msg.size() - width - 1;
        for (int i = remove_size; i >= 0; i--) {
            msg.pop_back();
        }
    }
}

void gabe::logging::utils::text_alignment::justify(std::string &msg, const int width) {}

// ================

gabe::logging::Logger::Logger() {}

gabe::logging::Logger::Logger(const gabe::logging::Severity& severity) : _severity(severity) {}

gabe::logging::Logger::Logger(const gabe::logging::Severity& severity, const gabe::logging::opts::Settings& settings) : _severity(severity), _settings(settings) {}

gabe::logging::Logger::Logger(gabe::logging::Logger&& logger) {
    // Closes the log file if it is opened
    _log_file.close();

    // Moves the opened file from the given Logger object
    _log_file = std::move(logger._log_file);
}

gabe::logging::Logger& gabe::logging::Logger::operator = (gabe::logging::Logger&& logger) {
    // Closes the log file if it is opened
    if (_log_file.is_open()) { _log_file.close(); }

    // Moves the opened file from the given Logger object
    _log_file = std::move(logger._log_file);

    return *this;
}

gabe::logging::Logger::~Logger() {
    // Closes the log file if it is opened
    if (_log_file.is_open()) { _log_file.close(); }
}

void gabe::logging::Logger::init() {
    // Creates the logs directory (if it exists, this function does nothing)
    std::filesystem::create_directory( _settings.logs_dir );

    // Opens the log file
    if (!_open_log_file()) {
        throw std::runtime_error("Logger not initialized. File could not be opened.");
    } 

    // Updates the control variable
    _is_working = true;
}

bool gabe::logging::Logger::_open_log_file() {
    // Closes the log file if it is opened
    if (_log_file.is_open()) { _log_file.close(); }

    // Opens the log file
    _log_file = std::ofstream (
        _settings.logs_dir + _settings.file_name + std::to_string(++_files_counter) + ".txt", std::ios::out
    );

    return !_log_file.fail();
}

std::string gabe::logging::Logger::_make_timestamp() {
    // Exits if the user does not want a timestamp
    if (_settings.log_template == gabe::logging::opts::LogTemplate::SEV_MSG) {
        return ""; // Empty timestamp
    }

    // Gets the time since epoch (tse)
    std::time_t tse = std::time(nullptr);

    // Gets the local time
    std::tm *tm = std::localtime(&tse);

    // Creates the timestamp string
    std::string timestamp = "[";

    // Checks if the user wants the calendar in the timestamp, and adds it to it if so
    if (_settings.time_template == opts::TimestampTemplate::CALENDAR_TIME) {
        timestamp += _get_calendar(tm, false);
    }
    else if (_settings.time_template == opts::TimestampTemplate::CALENDAR_YEAR_TIME) {
        timestamp += _get_calendar(tm, true);
    }

    // Adds a bracket separator between time and calendar, if the user chose to have calendar
    if (_settings.time_template != opts::TimestampTemplate::TIME) { timestamp += "]["; }

    // Adds the time
    timestamp += _get_time(tm);

    // Closes the timestamp
    timestamp += "]";

    return timestamp;
}

std::string gabe::logging::Logger::_get_calendar(std::tm* tm, bool include_year) {
    // Calendar variable that will be outputted
    std::string calendar;

    // Adds the Week day to the calendar
    calendar += utils::dicts::week_days.at(tm->tm_wday);

    // Adds a space
    calendar += " ";

    // Adds the Month to the calendar
    calendar += utils::dicts::months.at(tm->tm_mon);
    
    // Adds a space
    calendar += " ";

    // Adds the Day to the calendar
    calendar += tm->tm_mday < 10 ? "0" + std::to_string(tm->tm_mday) : std::to_string(tm->tm_mday);

    // If the user wants the year as well
    if (include_year) {
        // Adds a space
        calendar += " ";

        // Adds the Year to the calendar
        calendar += std::to_string( tm->tm_year + 1900 ); // + 1900, because tm_year gives the number of years since the epoch
    }

    return calendar;
}

std::string gabe::logging::Logger::_get_time(std::tm* tm) {
    // Time variable that will be outputted
    std::string time;

    // Adds the Hour
    time += tm->tm_hour < 10 ? "0" + std::to_string(tm->tm_hour) : std::to_string(tm->tm_hour);

    // Adds a delimiter
    time += ":";

    // Adds the Minutes
    time += tm->tm_min < 10 ? "0" + std::to_string(tm->tm_min) : std::to_string(tm->tm_min);

    // Adds a delimiter
    time += ":";

    // Adds the Seconds
    time += tm->tm_sec < 10 ? "0" + std::to_string(tm->tm_sec) : std::to_string(tm->tm_sec);

    return time;
}

void gabe::logging::Logger::_check_file_size() {
    // Checks if the current log file has reached the maximum size imposed
    if (_log_file.tellp() >= _settings.max_file_size) {
        // Opens a new log file
        if (!_open_log_file()) {
            // Updates thw working control variable
            _is_working = false;

            throw std::runtime_error("> Logger stopped working. New log file could not be opened.");
        }
    }
}

void gabe::logging::Logger::_write_header_log(gabe::logging::Severity severity, const std::string &message) {
    // Creates the extra strings needed for the header style
    std::string empty_line( _settings.max_line_size <= 0 ? message.size() + 4 : _settings.max_line_size, ' ' );
    std::string separ_line( _settings.max_line_size <= 0 ? message.size() + 4 : _settings.max_line_size, '*' );

    // Writes the extra strings
    _write_log(severity, "", empty_line, "", gabe::logging::utils::TextAligment::CENTER);
    _write_log(severity, "", separ_line, "", gabe::logging::utils::TextAligment::CENTER);

    // Writes the log message(s)
    _write_log(severity, "* ", message, " *", gabe::logging::utils::TextAligment::CENTER);

    // Finishes the Header logging with the separator extra string
    _write_log(severity, "", separ_line, "", gabe::logging::utils::TextAligment::CENTER);
}

void gabe::logging::Logger::_write_subheader_log(gabe::logging::Severity severity, const std::string &message) {
    // Writes the log message(s)
    _write_log(severity, "~~~~> ", message, " <~~~~", gabe::logging::utils::TextAligment::CENTER);
}

void gabe::logging::Logger::_write_normal_log(gabe::logging::Severity severity, const std::string &message) {
    // Writes the log message(s)
    _write_log(severity, "", message, "", gabe::logging::utils::TextAligment::LEFT);
}

void gabe::logging::Logger::_write_log(gabe::logging::Severity severity, const std::string &pre_message, std::string message, const std::string &pos_message, utils::TextAligment text_alignment) {
    // Severity check
    if ((uint8_t)severity < (uint8_t)_severity) { return; }

    // Gets the beginning and the end of the log
    std::string log_begin = _make_begin_log(severity);
    std::string log_end = _make_end_log();

    // Creates the middle of the log
    std::string log_middle;

    // Checks if the user cares about the maximum line size
    if (_settings.max_line_size > 0) {
        // Calculates the size to remove from the message
        int size_to_remove = message.size() + pre_message.size() + pos_message.size() - _settings.max_line_size;

        // Checks if the user wants multiple log lines, or just a single one
        if (_settings.mult_line_logs) {
            // Keeps writting until there isnt a line that needs to be shredder
            while (size_to_remove > 0) {
                // Creates the current message
                std::string cur_message(message.begin(), message.begin() + _settings.max_line_size - pre_message.size() - pos_message.size());

                // Adds the pre and pos messages
                cur_message.insert( cur_message.begin(), pre_message.begin(), pre_message.end() );
                cur_message += pos_message;

                // Adds the log begin and end to the final log
                cur_message.insert( cur_message.begin(), log_begin.begin(), log_begin.end() );
                cur_message += log_end;

                // Writes the log
                _log_file.write( cur_message.c_str(), cur_message.size() );

                // Removes the previous written content
                message.erase(message.begin(), message.begin() + _settings.max_line_size - pre_message.size() - pos_message.size());

                // Keeps deleting empty spaces for the next message
                while (message[0] == ' ') { message.erase( message.begin() ); }

                // Updates the size to be removed
                size_to_remove = message.size() + pre_message.size() + pos_message.size() - _settings.max_line_size;
            }
        }
        else {
            // Checks if the message has to much size
            if (size_to_remove > 0) {
                gabe::logging::utils::text_alignment::left(message, message.size() - size_to_remove - 6);

                // Adds the indicator of message cutted
                message += " (...)";
            }
        }

        if (text_alignment == gabe::logging::utils::TextAligment::LEFT) {
            gabe::logging::utils::text_alignment::left(message, _settings.max_line_size - pre_message.size() - pos_message.size());
        }
        else if (text_alignment == gabe::logging::utils::TextAligment::RIGHT) {
            gabe::logging::utils::text_alignment::right(message, _settings.max_line_size - pre_message.size() - pos_message.size());
        }
        else if (text_alignment == gabe::logging::utils::TextAligment::CENTER) {
            gabe::logging::utils::text_alignment::center(message, _settings.max_line_size - pre_message.size() - pos_message.size());
        }
        else if (text_alignment == gabe::logging::utils::TextAligment::JUSTIFY) {
        }
    }

    // Appends the message together
    log_middle += pre_message + message + pos_message;

    // Adds the log begin and end to the final log
    log_middle.insert( log_middle.begin(), log_begin.begin(), log_begin.end() );
    log_middle += log_end;

    // Writes the log
    _log_file.write( log_middle.c_str(), log_middle.size() );
}

std::string gabe::logging::Logger::_make_begin_log(gabe::logging::Severity severity) {
    // Log variable of the log beginning that will be outputted
    std::string log_begin;

    // Checks if the log template has the time in the beginning
    if (_settings.log_template == gabe::logging::opts::LogTemplate::TIME_SEV_MSG) {
        // Inserts the timestamp in the beginning
        log_begin += _make_timestamp();
    }

    // Adds the Severity level
    log_begin += utils::dicts::severity_levels.at(severity);

    // Checks if the log template has the time after the Severity
    if (_settings.log_template == gabe::logging::opts::LogTemplate::SEV_TIME_MSG) {
        // Inserts the timestamp after the Severity
        log_begin += _make_timestamp();
    }

    // Finishes the beginning of the log with a space
    log_begin += " ";

    return log_begin;
}

std::string gabe::logging::Logger::_make_end_log() {
    // Log variable of the log end that will be outputted
    std::string log_end;

    // Checks if the log template has the time at the end
    if (_settings.log_template == gabe::logging::opts::LogTemplate::SEV_MSG_TIME) {
        // Adds the timestamp at the end
        log_end += " " + _make_timestamp();
    }

    // Finishes the end of the log with a line break
    log_end += "\n";

    return log_end;
}

void gabe::logging::Logger::set_severity(const gabe::logging::Severity& severity) { _severity = severity; }
