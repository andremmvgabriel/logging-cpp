#pragma once 

namespace gabe {
    namespace logging {
        enum class SeverityLevel
        {
            TRACE   =   0b000001,
            DEBUG   =   0b000010,
            INFO    =   0b000100,
            WARNING =   0b001000,
            ERROR   =   0b010000,
            FATAL   =   0b100000
        };
    }
}