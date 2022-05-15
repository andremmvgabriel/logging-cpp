#include <gtest/gtest.h>

#include <string>

#include <gabe/logging/formatters/Calendar.hpp>


TEST(Basic, FormatWithKey) {
    std::string initial_message = "[%cal] Log message with key! Calendar should be displayed.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 7 );
}
 
TEST(Basic, FormatWithoutKey) {
    std::string initial_message = "[%time] Log message without expected key... Calendar should be missing.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message == format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() );
}

TEST(Basic, FormatWithMultipleKeys) {
    std::string initial_message = "[%cal] Log message with two keys... Calendar should appear in the first one [%cal]";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 7 );

    std::size_t key_pos = format_message.find("%cal");

    ASSERT_TRUE( key_pos != -1 );
}

TEST(LayoutKeys, Year) {
    std::string initial_message = "[%cal] This message should only present the year.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format("%year");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() );
}

TEST(LayoutKeys, Month_asNumeric) {
    std::string initial_message = "[%cal] This message should only present the month (numeric).";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format("%month");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 2 );
}

TEST(LayoutKeys, Month_asString) {
    std::string initial_message = "[%cal] This message should only present the month (string).";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format("%smonth");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 1 );
}

TEST(LayoutKeys, Day) {
    std::string initial_message = "[%cal] This message should only present the day.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format("%day");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 2 );
}

TEST(LayoutKeys, Week_asNumeric) {
    std::string initial_message = "[%cal] This message should only present the week day (numeric).";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format("%week");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 3 );
}

TEST(LayoutKeys, Week_asString) {
    std::string initial_message = "[%cal] This message should only present the week day (numeric).";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format("%sweek");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 1 );
}

TEST(Layouts, YearMonthDay) {
    std::string initial_message = "[%cal] This message should only contain year + month (numeric) + day.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format("%year/%month/%day");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 6 );
}

TEST(Layouts, YearMonthDayWeek) {
    std::string initial_message = "[%cal] This message should only contain year + month (numeric) + day + week (numeric).";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format("%year/%month/%day %week");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 8 );
}

TEST(Layouts, LayoutWithDuplicatedKeys) {
    std::string initial_message = "[%cal] This message should only contain year + month (string) + day, and the same layout without formatting.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format("%year/%smonth/%day %year/%smonth/%day");
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 26 );
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
