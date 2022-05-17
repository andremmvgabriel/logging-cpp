#pragma once

#include <string>

namespace gabe {
    namespace logging {
        namespace formatters {
            class Formatter
            {            
            protected:
                std::string _type;
                std::string _key;
                std::string _layout;
            
            protected:
                virtual std::string _format();
            
            public:
                Formatter();
                Formatter(const std::string &type, const std::string &key);

                std::string type() const;
                std::string key() const;

                virtual void format(std::string &message);
            };
        }
    }
}
