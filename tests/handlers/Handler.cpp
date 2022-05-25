#include <gtest/gtest.h>

#include <string>

#include <gabe/logging/handlers/Handler.hpp>

namespace glh = gabe::logging::handlers;

TEST(Constructor, Default) {
    glh::Handler handler;

    ASSERT_TRUE( handler.type() == "DefaultHandler" );
}

TEST(Constructor, Type) {
    glh::Handler handler("CustomTypeNameHandler");

    ASSERT_TRUE( handler.type() == "CustomTypeNameHandler" );
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
