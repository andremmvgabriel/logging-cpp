#pragma once

#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <stdint.h>

namespace gabe {
    namespace logging {
        namespace core {
            /**
             * @brief Sink object.
             * 
             * This class is aimed to manage the logging data that was logged into a Logger object and has to be written in a file. This class also manages multiple log files, in case it has to be rotated by a Handler.
             */
            class Sink
            {
            protected:
                /**
                 * @brief Logging file.
                 */
                std::ofstream _file;

                /**
                 * @brief Base name of the logging file.
                 */
                std::string _file_name;

                /**
                 * @brief Directory of the log file.
                 */
                std::string _file_directory;

                /**
                 * @brief Buffer to stash logging data before writting into file. 
                 */
                char *_buffer = nullptr;

                /**
                 * @brief Maximum size of the buffer.
                 */
                uint32_t _buffer_size = 500000;

                /**
                 * @brief Buffer write position.
                 */
                uint32_t _buffer_pos = 0;
            
            public:
                /**
                 * @brief Construct a new Sink object.
                 * 
                 * Default constructor. This method creates a Sink object with the log file as "log.txt", and its directory as a relative path to the program executable. 
                 */
                Sink();

                /**
                 * @brief Construct a new Sink object.
                 * 
                 * Full path constructor. This method creates a Sink object with a given log file name and directory.
                 * 
                 * @param file_directory Path to the log file.
                 * @param file_name Log file name.
                 */
                Sink(const std::string &file_directory, const std::string &file_name);

                /**
                 * @brief Destroy the Sink object.
                 */
                ~Sink();

                /**
                 * @brief Opens the log file in write only mode.
                 * 
                 * @note If the file is already opened, the function exits immediately without throwing any exception/error.
                 */
                void open_file();

                /**
                 * @brief Closes the opened log file.
                 * 
                 * @note If the file is not opened, the function exits immediately without throwing any exception/error.
                 */
                void close_file();

                /**
                 * @brief Adds the message to the sink buffer.
                 * 
                 * @param message Message to sink in the buffer.
                 */
                void sink_in(const std::string &message);

                /**
                 * @brief Flushes the data in the buffer into the log file.
                 * 
                 * Writes the data stashed in the buffer into the log file. Also restarts the buffer writting position.
                 */
                void flush();

                /**
                 * @brief Analyses if the buffer data should be flushed into the log file.
                 * 
                 * @param message Message to sink in. 
                 * @return bool Should/Shouldn't flush the buffer into the log file.
                 */
                bool should_flush(const std::string &message);

                /**
                 * @brief Renames the log file.
                 * 
                 * Once called, this functions makes sure that the log file is properly closed, and then proceeds to rename it with the new given name. This is commonly used by log file Handlers, that the user may want to add to the Logger object.
                 * 
                 * @param new_name New name of the log file.
                 */
                void rotate_file(const std::string &new_name);

                /**
                 * @brief Get the current size of the file.
                 * 
                 * @return uint32_t File size.
                 */
                uint32_t file_size();

                /**
                 * @brief Get the current size of the buffer.
                 * 
                 * @return uint32_t Buffer size.
                 */
                uint32_t buffer_size();
                
                /**
                 * @brief Gets the maximum size of the buffer.
                 * 
                 * @return uint32_t Buffer maximum size.
                 */
                uint32_t buffer_max_size();

                /**
                 * @brief Set the name of the log file.
                 * 
                 * @param name Name of the log file.
                 */
                void set_file_name(const std::string &name);

                /**
                 * @brief Get the name of the log file.
                 * 
                 * @return std::string Name of the log file.
                 */
                std::string get_file_name();

                /**
                 * @brief Set the path to the log file.
                 * 
                 * @param directory Path to the log file.
                 */
                void set_file_directory(const std::string &directory);

                /**
                 * @brief Get the path to the log file.
                 * 
                 * @return std::string Path to the log file.
                 */
                std::string get_file_directory();

                /**
                 * @brief Get the full path to the log file.
                 * 
                 * @return std::string Full path to the log file.
                 */
                std::string get_file_full_path();
            };
        }
    }
}
