#pragma once 

namespace gabe {
    namespace logging {
        /**
         * @brief Severity Levels enumerator.
         * 
         * This enumerator contains all the logging severity levels allowed in the logging library.
         */
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