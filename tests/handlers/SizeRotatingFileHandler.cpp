#include <gtest/gtest.h>

#include <string>

#include <gabe/logging/handlers/SizeRotatingFileHandler.hpp>

namespace glh = gabe::logging::handlers;


class SizeRotatingFileHandlerMocker : public glh::SizeRotatingFileHandler
{
public:
    using glh::SizeRotatingFileHandler::_size;
    using glh::SizeRotatingFileHandler::_files_counter;
};


TEST(Constructor, Default) {
    SizeRotatingFileHandlerMocker handler;

    ASSERT_TRUE( handler.type() == "SizeRotatingFileHandler" );
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
