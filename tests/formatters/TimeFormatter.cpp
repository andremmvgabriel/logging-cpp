#include <gtest/gtest.h>
#include <string>

#include <gabe/logging/formatters/Time.hpp>


TEST(TimeFormatter, FormatMessageWithKey) {
    std::string initial_message = "[%time] Log message with key! Time should be displayed.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
}
 
TEST(TimeFormatter, FormatMessageWithoutKey) {
    std::string initial_message = "[Oh No] Log message without key... Time should be missing.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(initial_message);

    ASSERT_TRUE( initial_message == format_message );
}

TEST(TimeFormatter, FormatMessageWithIncorrentKey) {
    std::string initial_message = "[%calendar] Log message with calendar key... Time should be missing.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(initial_message);

    ASSERT_TRUE( initial_message == format_message );
}

TEST(TimeFormatter, FormatMessageWithMultipleKeys) {
    std::string initial_message = "[%time] Log message with two keys... Time should appear in the first one [%time]";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(initial_message);

    ASSERT_TRUE( initial_message != format_message );

    std::size_t key_pos = format_message.find("%time");

    ASSERT_TRUE( key_pos != -1 );
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
