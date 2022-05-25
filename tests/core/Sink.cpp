#include <gtest/gtest.h>
#include <fstream>

#include <gabe/logging/core/Sink.hpp>


class SinkMocker : public gabe::logging::core::Sink
{
public:
    using Sink::_buffer;

    SinkMocker() : Sink() {}
    SinkMocker(const std::string &file_directory, const std::string &file_name) : Sink(file_directory, file_name) {}
};



TEST(Core, CreateSink) {
    // Default constructor
    SinkMocker sink1;

    ASSERT_TRUE(sink1._buffer != nullptr);
    ASSERT_TRUE(sink1.buffer_size() == 0);
    ASSERT_TRUE(sink1.buffer_max_size() == 500000);
    ASSERT_TRUE(sink1.file_size() == 0);
    ASSERT_TRUE(sink1.file_name() == "log.txt");
    ASSERT_TRUE(sink1.file_directory() == "/home/gabe/Projects/Logger/build/tests/core");
    ASSERT_TRUE(sink1.file_full_path() == "/home/gabe/Projects/Logger/build/tests/core/log.txt");

    // Directory + log name constructor
    SinkMocker sink2 ("path/to/logs", "log_file_name.txt");

    ASSERT_TRUE(sink2._buffer != nullptr);
    ASSERT_TRUE(sink1.buffer_size() == 0);
    ASSERT_TRUE(sink1.buffer_max_size() == 500000);
    ASSERT_TRUE(sink1.file_size() == 0);
    ASSERT_TRUE(sink2.file_name() == "log_file_name.txt");
    ASSERT_TRUE(sink2.file_directory() == "path/to/logs");
    ASSERT_TRUE(sink2.file_full_path() == "path/to/logs/log_file_name.txt");
}

TEST(Core, ShouldFlush) {
    SinkMocker sink;

    std::string smaller_message = std::string(499999, '*');
    std::string equal_message = std::string(500000, '*');
    std::string bigger_messsage = std::string(500001, '*');

    ASSERT_TRUE(sink.should_flush(smaller_message) == false);
    ASSERT_TRUE(sink.should_flush(equal_message) == false);
    ASSERT_TRUE(sink.should_flush(bigger_messsage) == true);
}

TEST(Core, SinkIn) {
    SinkMocker sink;

    std::string message_to_sink = "Sink me please!";

    sink.sink_in(message_to_sink);

    ASSERT_TRUE(sink.file_size() == 0);
    ASSERT_TRUE(sink.buffer_size() == message_to_sink.size());
    ASSERT_TRUE(message_to_sink[sink.buffer_size() - 1] == '!');

    for (int i = 0; i < sink.buffer_size(); i++) {
        ASSERT_TRUE(sink._buffer[i] == message_to_sink[i]);
    }
}

TEST(Core, Flush) {
    SinkMocker sink;

    std::string message = "Message to sink! And then flush";

    sink.sink_in(message);
    sink.flush();

    ASSERT_TRUE(sink.file_size() == message.size());
    ASSERT_TRUE(sink.buffer_size() == 0);
}

// TEST(Core, DestroySink) {
//     SinkMocker sink;

//     ASSERT_TRUE(sink._buffer == nullptr);
// }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
