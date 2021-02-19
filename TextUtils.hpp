#pragma once

#include <iostream>
#include <string>

namespace TextUtils
{
    namespace Alignment
    {
        void left(std::string &msg, const int width);

        void right(std::string &msg, const int width);

        void center(std::string &msg, const int width);

        void justify(std::string &msg, const int width);
    } // namespace Alignment
} // namespace TextUtils
