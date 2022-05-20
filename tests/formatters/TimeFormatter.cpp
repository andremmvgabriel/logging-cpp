#include <gtest/gtest.h>
#include <string>

#include <gabe/logging/formatters/Time.hpp>



TEST(SingleKey, HourKey) {
    std::string initial_message = "[%hour] Log message with hour key! Current hour should be displayed.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 3 );
}

TEST(SingleKey, MinutesKey) {
    std::string initial_message = "[%min] Log message with minutes key! Current minutes should be displayed.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 2 );
}

TEST(SingleKey, SecondsKey) {
    std::string initial_message = "[%sec] Log message with seconds key! Current seconds should be displayed.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 2 );
}

TEST(SingleKey, MillisecondsKey) {
    std::string initial_message = "[%ms] Log message with milliseconds key! Current milliseconds should be displayed.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() );
}

TEST(SingleKey, EpochKey) {
    std::string initial_message = "[%epoch] Log message with epoch key! Time since epoch should be displayed.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 4 );
}

TEST(MultipleKeys, Layout_hour_min_sec) {
    std::string initial_message = "[%hour:%min:%sec] Log message with hour, minutes, and seconds keys! Time should be displayed as hh:mm:ss.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 7 );
}

TEST(MultipleKeys, Layout_hour_min_sec_ms) {
    std::string initial_message = "[%hour:%min:%sec.%ms] Log message with hour, minutes, seconds, and milliseconds keys! Time should be displayed as hh:mm:ss.ms.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 7 );
}

TEST(MultipleKeys, Layout_epoch_ms) {
    std::string initial_message = "[%epoch.%ms] Log message with epoch and milliseconds keys! Time should be displayed as epoch.ms.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() - 4 );
}

TEST(Exceptions, NoKey) {
    std::string initial_message = "[NoKey] Log message without any key... Time should be missing.";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message == format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() );
}

TEST(Exceptions, DuplicatedKeys) {
    std::string initial_message = "[%hour %hour] Log message with two hour keys! The current hour should only be displayed in the first key";
    std::string format_message = initial_message;

    gabe::logging::formatters::Time time_format;
    time_format.format(format_message);

    ASSERT_TRUE( initial_message != format_message );
    ASSERT_TRUE( initial_message.size() == format_message.size() + 3 );
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
