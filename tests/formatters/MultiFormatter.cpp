#include <gtest/gtest.h>
#include <string>

#include <gabe/logging/formatters/MultiFormatter.hpp>

namespace glf = gabe::logging::formatters;


class MultiFormatterMocker : public glf::MultiFormatter
{
public:
    using glf::MultiFormatter::_formatters;

    MultiFormatterMocker() : MultiFormatter() {}
    MultiFormatterMocker(const std::string &type) : MultiFormatter(type) {}
};


TEST(Constructor, Default) {
    MultiFormatterMocker formatter;

    ASSERT_TRUE( formatter.type() == "MultiFormatter" );
    ASSERT_TRUE( formatter.key() == "" );
    ASSERT_TRUE( formatter._formatters.size() == 0 );
}

TEST(Constructor, Type) {
    MultiFormatterMocker formatter("TypeMultiFormatter");

    ASSERT_TRUE( formatter.type() == "TypeMultiFormatter" );
    ASSERT_TRUE( formatter.key() == "" );
}

TEST(Core, AddFormatter) {
    MultiFormatterMocker formatter;

    // Add first formatter
    MultiFormatterMocker sub_formatter1("F1");
    formatter.add_formatter(sub_formatter1);
    ASSERT_TRUE( formatter._formatters.size() == 1 );

    // Add second formatter
    MultiFormatterMocker sub_formatter2("F2");
    formatter.add_formatter(sub_formatter2);
    ASSERT_TRUE( formatter._formatters.size() == 2 );

    // Add third formatter with same type as first one
    MultiFormatterMocker sub_formatter3("F1");
    ASSERT_TRUE( formatter._formatters.size() == 2 );
}

TEST(Core, format) {
    MultiFormatterMocker formatter;

    std::string message = "[%key1] [%key2] This message should remain the same. MultiFormatter format executes the format of its internal formatters.";

    formatter.format(message);

    ASSERT_TRUE( message == "[%key1] [%key2] This message should remain the same. MultiFormatter format executes the format of its internal formatters.");
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
