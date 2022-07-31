#pragma once

#include <vector>
#include <string>

#include <gabe/logging/core/Sink.hpp>
#include <gabe/logging/handlers/Handler.hpp>

namespace gabe {
    namespace logging {
        namespace handlers {
            /**
             * @brief Size Rotating File handler object.
             * 
             * This class is responsible for a handling the logger log files based on their size.
             */
            class SizeRotatingFileHandler : public Handler
            {
            protected:
                /**
                 * @brief Size of the log files. 
                 */
                uint64_t _size;

                /**
                 * @brief Log files counter.
                 */
                uint16_t _files_counter = 0;
            
            protected:
                std::string _find_last_and_get_after(const std::string &target, const std::string &key);

                std::vector<std::string> _find_log_files(const std::string &directory, const std::string &file_name);

                void _update_files_counter(const std::vector<std::string> &log_files);

            public:
                /**
                 * @brief Construct a new Size Rotating File Handler object.
                 */
                SizeRotatingFileHandler();

                /**
                 * @brief Construct a new Size Rotating File Handler object.
                 * 
                 * @param size Log files size.
                 */
                SizeRotatingFileHandler(uint64_t size);

                /**
                 * @brief Evaluates a given logger sink to update internal management variables.
                 * 
                 * This method is abstract and is designed to be overritten by a child class. It's behaviour should be written accordingly to child class needs to update its internal management variables.
                 * 
                 * In this class, it checks how many files with the sink log file name already exist in the log files directory, and updates the log files counter accordingly.
                 * 
                 * @param sink Pointer to the logger sink.
                 */
                virtual void check_sink(core::Sink *sink) override;

                /**
                 * @brief Evaluates if the logger log file needs to be managed by the handler.
                 * 
                 * This method is abstract and is designed to be overritten by a child class. It's behaviour should be written accordingly to child class needs to confirm is the file should or not should be handled at the calling moment.
                 * 
                 * In this class, evaluates the size of the log message, the buffer, and the log file, and compares it with the max log file size given at its constructor.
                 * 
                 * @param sink Pointer to the logger sink.
                 * @param message Log message.
                 * @return bool Should/Shouldn't manage log file.
                 */
                virtual bool evaluate(core::Sink *sink, const std::string &message) override;

                /**
                 * @brief Creates a new file name for the logger file.
                 * 
                 * This method is abstract and is designed to be overritten by a child class. It's behaviour should be written accordingly to child class needs to rename the logger log file.
                 * 
                 * In this class, it returns the given log file name with the respectively counter.
                 * 
                 * @param file_name Current log file name.
                 * @return std::string Handled log file name.
                 */
                virtual std::string create_handled_file_name(const std::string &file_name) override;
            };
        }
    }
}
