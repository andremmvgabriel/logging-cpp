#include <gtest/gtest.h>

#include <string>

#include <gabe/logging/handlers/ConsoleStdOutHandler.hpp>

namespace glh = gabe::logging::handlers;


TEST(Constructor, Default) {
    glh::ConsoleStdOutHandler handler;

    ASSERT_TRUE( handler.type() == "ConsoleStdOutHandler" );
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
