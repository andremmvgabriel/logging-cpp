#include <gtest/gtest.h>

#include <gabe/logging/core/Sink.hpp>


class SinkMocker : public gabe::logging::core::Sink
{
public:
    using Sink::_buffer;
    using Sink::_buffer_pos;

    // ~SinkMocker() { ~Sink(); }
};



TEST(Core, CreateSink) {
    SinkMocker sink;

    ASSERT_TRUE(sink._buffer != nullptr);
    ASSERT_TRUE(sink._buffer_pos == 0);
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

    ASSERT_TRUE(sink._buffer_pos == message_to_sink.size());
    ASSERT_TRUE(message_to_sink[sink._buffer_pos - 1] == '!');

    for (int i = 0; i < sink._buffer_pos; i++) {
        ASSERT_TRUE(sink._buffer[i] == message_to_sink[i]);
    }
}

TEST(Core, DestroySink) {
    SinkMocker sink;
    sink.~Sink();

    ASSERT_TRUE(sink._buffer == nullptr);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}