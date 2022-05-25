#include <gtest/gtest.h>
#include <string>

#include <gabe/logging/formatters/Formatter.hpp>

namespace glf = gabe::logging::formatters;

TEST(Constructor, Default) {
    glf::Formatter formatter;

    ASSERT_TRUE( formatter.type() == "DefaultFormatter" );
    ASSERT_TRUE( formatter.key() == "" );
}

TEST(Constructor, Type) {
    glf::Formatter formatter("TypeConstructorFormatter");

    ASSERT_TRUE( formatter.type() == "TypeConstructorFormatter" );
    ASSERT_TRUE( formatter.key() == "" );
}

TEST(Constructor, TypeAndKey) {
    glf::Formatter formatter("TypeKeyConstructorFormatter", "NiceKey");

    ASSERT_TRUE( formatter.type() == "TypeKeyConstructorFormatter" );
    ASSERT_TRUE( formatter.key() == "NiceKey" );
}

TEST(Format, WithoutKey) {
    glf::Formatter formatter("TypeKeyConstructorFormatter", "%key_to_find");

    std::string message = "[%different_key] This message should remain the same.";

    formatter.format(message);

    ASSERT_TRUE( message == "[%different_key] This message should remain the same.");
}

TEST(Format, WithKey) {
    glf::Formatter formatter("TypeKeyConstructorFormatter", "%key_to_find");

    std::string message = "[%key_to_find] This message should replace the key with the formatting that the formatter do. Abstract one just removes the key.";

    formatter.format(message);

    ASSERT_TRUE( message == "[] This message should replace the key with the formatting that the formatter do. Abstract one just removes the key.");
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
