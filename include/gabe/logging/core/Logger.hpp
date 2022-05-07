#pragma once

#include <fstream>
#include <unordered_map>

#include <gabe/logging/SeverityLevel.hpp>
#include <gabe/logging/handlers/Handler.hpp>

namespace gabe {
    namespace logging {
        namespace core {
            class Logger
            {
            protected:
                std::ofstream _log_file;

                SeverityLevel _severity = SeverityLevel::INFO;

                std::unordered_map<std::string, handlers::Handler*> _handlers;
            
            protected:
                void _open_log_file();

            public:
                Logger();
                Logger(const SeverityLevel &severity);

                ~Logger();

                void log(const SeverityLevel &severity, const std::string &message);

                template<typename HandlerT>
                void add_handler(const HandlerT& handler) {
                    HandlerT* handler_copy = new HandlerT();
                    *handler_copy = handler;
                    
                    if (_handlers.find(handler.type()) != _handlers.end()) {
                        delete _handlers[handler.type()];
                    }

                    _handlers[handler.type()] = dynamic_cast<handlers::Handler*>(handler_copy);
                }

                // template<typename T>
                // inline void add(const T& t)
                // {
                //     static std::vector<DerT> v;
                //     T* local = new T();
                //     (*local) = t;
                //     v.push_back(dynamic_cast<Der*>(local));

                //     v[0]->specific();
                // }
                // requires std::is_base_of<T, Der>
            };
        }
    }
}
