#include <gtest/gtest.h>
#include <string>

#include <gabe/logging/formatters/Time.hpp>


TEST(Basic, FormatWithKey) {
    std::string initial_message = "[%time] Log message with key! Time should be displayed.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 7 );
}
 
TEST(Basic, FormatWithoutKey) {
    std::string initial_message = "[%cal] Log message without expected key... Time should be missing.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message == format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() );
}

TEST(Basic, FormatWithMultipleKeys) {
    std::string initial_message = "[%time] Log message with two keys... Time should appear in the first one [%time]";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 7 );

    std::size_t key_pos = format_message.find("%time");

    ASSERT_TRUE( key_pos != -1 );
}

TEST(LayoutKeys, Hours) {
    std::string initial_message = "[%time] This message should only present the two digit hours.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time calendar_format("%hour");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 3);
}

TEST(LayoutKeys, Minutes) {
    std::string initial_message = "[%time] This message should only present the two digit minutes.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time calendar_format("%min");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 3);
}

TEST(LayoutKeys, Seconds) {
    std::string initial_message = "[%time] This message should only present the two digit seconds.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time calendar_format("%sec");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 3);
}

TEST(LayoutKeys, Milliseconds) {
    std::string initial_message = "[%time] This message should only present the three digits milliseconds.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time calendar_format("%ms");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 2);
}

TEST(LayoutKeys, Epoch) {
    std::string initial_message = "[%time] This message should only present the 10 digits epoch.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time calendar_format("%epoch");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 5);
}

TEST(Layouts, Clock) {
    std::string initial_message = "[%time] This message should present the clock as hh:mm:ss.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time calendar_format("%hour:%min:%sec");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 3);
}

TEST(Layouts, ClockWithMilliseconds) {
    std::string initial_message = "[%time] This message should present the clock as hh:mm:ss.ms.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time calendar_format("%hour:%min:%sec.%ms");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 7);
}

TEST(Layouts, EpochWithMilliseconds) {
    std::string initial_message = "[%time] This message should present the time as epoch.ms.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time calendar_format("%epoch.%ms");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 9);
}

TEST(Layouts, LayoutWithDuplicatedKeys) {
    std::string initial_message = "[%time] This message should only contain clock as hh:mm:ss, and the same layout without formatting.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time calendar_format("%hour:%min:%sec %hour:%min:%sec");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 19 );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
