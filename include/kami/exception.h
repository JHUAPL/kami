//
// Created by James Howard on 9/9/22.
//

#ifndef KAMI_EXCEPTION_H
//! @cond SuppressGuard
#define KAMI_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace kami::exception {

    class AgentNotFound : public std::logic_error {
    public:
        explicit AgentNotFound(const char *s) : std::logic_error(s) {};

        explicit AgentNotFound(const std::string &s) : std::logic_error(s) {};
    };

    class InvalidOption : public std::invalid_argument {
    public:
        explicit InvalidOption(const char *s) : std::invalid_argument(s) {};

        explicit InvalidOption(const std::string &s) : std::invalid_argument(s) {};
    };

    class LocationUnavailable : public std::domain_error {
    public:
        explicit LocationUnavailable(const char *s) : std::domain_error(s) {};

        explicit LocationUnavailable(const std::string &s) : std::domain_error(s) {};
    };

    class ResourceNotAvailable : public std::logic_error {
    public:
        explicit ResourceNotAvailable(const char *s) : std::logic_error(s) {};

        explicit ResourceNotAvailable(const std::string &s) : std::logic_error(s) {};
    };

}

#endif //KAMI_EXCEPTION_H
