#include <gtest/gtest.h>

#include <string>

#include <gabe/logging/formatters/Calendar.hpp>



TEST(SingleKey, YearKey) {
    std::string initial_message = "[%year] Log message with year key! Current year should be displayed.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 1 );
}

TEST(SingleKey, MonthKey_asNumeric) {
    std::string initial_message = "[%month] Log message with month key! Current month should be displayed as 2 numeric digits.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 4 );
}

TEST(SingleKey, MonthKey_asString) {
    std::string initial_message = "[%smonth] Log message with month key! Current month should be displayed as 3 characters string.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 4 );
}

TEST(SingleKey, DayKey) {
    std::string initial_message = "[%day] Log message with day key! Current day should be displayed.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 2 );
}

TEST(SingleKey, WeekKey_asNumeric) {
    std::string initial_message = "[%week] Log message with week key! Current week should be displayed as 1 digits number.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 4 );
}

TEST(SingleKey, WeekKey_asString) {
    std::string initial_message = "[%sweek] Log message with week key! Current week should be displayed as 3 characters string.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 3 );
}

TEST(MultipleKeys, Layout_Year_Month_Day_Week) {
    std::string initial_message = "[%year %month %day %week] Log message with year, month, day, and week keys! Calendar should be displayed as YYYY MM DD W.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 11 );
}

TEST(MultipleKeys, Layout_Year_SMonth_Day_Week) {
    std::string initial_message = "[%year %smonth %day %week] Log message with year, smonth, day, and week keys! Calendar should be displayed as YYYY Mon DD W.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 11 );
}

TEST(MultipleKeys, Layout_Year_Month_Day_SWeek) {
    std::string initial_message = "[%year %month %day %sweek] Log message with year, month, day, and sweek keys! Calendar should be displayed as YYYY MM DD Wee.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 10 );
}

TEST(MultipleKeys, Layout_Year_SMonth_Day_SWeek) {
    std::string initial_message = "[%year %smonth %day %sweek] Log message with year, smonth, day, and sweek keys! Calendar should be displayed as YYYY Mon DD Wee.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 10 );
}

TEST(Exceptions, NoKey) {
    std::string initial_message = "[NoKey] Log message without any key... Calendar should be missing.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message == format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() );
}

TEST(Exceptions, DuplicatedKeys) {
    std::string initial_message = "[%year %year] Log message with two year keys! The current year should only be displayed in the first key";
    std::string format_message = initial_message;

    gabe::logging::formatters::Calendar calendar_format;
    calendar_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 1 );
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
