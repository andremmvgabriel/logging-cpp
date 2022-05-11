#include <gtest/gtest.h>
#include <string>

#include <gabe/logging/formatters/Calendar.hpp>


TEST(CalendarFormatter, FormatMessageWithKey) {
    std::string initial_message = "[%calendar] Log message with key! Calendar should be displayed.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
}
 
TEST(CalendarFormatter, FormatMessageWithoutKey) {
    std::string initial_message = "[Oh No] Log message without key... Calendar should be missing.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message == format_message );
}

TEST(CalendarFormatter, FormatMessageWithIncorrentKey) {
    std::string initial_message = "[%time] Log message with time key... Calendar should be missing.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message == format_message );
}

TEST(CalendarFormatter, FormatMessageWithMultipleKeys) {
    std::string initial_message = "[%calendar] Log message with two keys... Calendar should appear in the first one [%calendar]";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );

    std::size_t key_pos = format_message.find("%calendar");

    ASSERT_TRUE( key_pos != -1 );
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
