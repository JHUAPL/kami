//
// Created by James Howard on 9/9/22.
//

#ifndef KAMI_ERROR_H
//! @cond SuppressGuard
#define KAMI_ERROR_H
//! @endcond

#include <stdexcept>
#include <string>

namespace kami::error {

    /**
     * @brief Agent was not found
     */
    class AgentNotFound
            : public std::logic_error {
    public:
        /**
         * @brief Constructor
         * @param s text description of the exception
         */
        explicit AgentNotFound(const char* s)
                :std::logic_error(s) {
        };

        /**
         * @brief Constructor
         * @param s text description of the exception
         */
        explicit AgentNotFound(const std::string& s)
                :std::logic_error(s) {
        };
    };

    /**
     * @brief Location specified is invalid
     *
     * @see `LocationUnavailable`
     */
    class LocationInvalid
            : public std::domain_error {
    public:
        /**
         * @brief Constructor
         * @param s text description of the exception
         */
        explicit LocationInvalid(const char* s)
                :std::domain_error(s) {
        };

        /**
         * @brief Constructor
         * @param s text description of the exception
         */
        explicit LocationInvalid(const std::string& s)
                :std::domain_error(s) {
        };
    };

    /**
     * @brief Location specified is unavailable
     *
     * @see `LocationInvalid`
     */
    class LocationUnavailable
            : public std::domain_error {
    public:
        /**
         * @brief Constructor
         * @param s text description of the exception
         */
        explicit LocationUnavailable(const char* s)
                :std::domain_error(s) {
        };

        /**
         * @brief Constructor
         * @param s text description of the exception
         */
        explicit LocationUnavailable(const std::string& s)
                :std::domain_error(s) {
        };
    };

    /**
     * @brief The option given is not valid at this time
     */
    class OptionInvalid
            : public std::invalid_argument {
    public:
        /**
         * @brief Constructor
         * @param s text description of the exception
         */
        explicit OptionInvalid(const char* s)
                :std::invalid_argument(s) {
        };

        /**
         * @brief Constructor
         * @param s text description of the exception
         */
        explicit OptionInvalid(const std::string& s)
                :std::invalid_argument(s) {
        };
    };

    /**
     * @brief The resource specified is not available at this time
     */
    class ResourceNotAvailable
            : public std::logic_error {
    public:
        /**
         * @brief Constructor
         * @param s text description of the exception
         */
        explicit ResourceNotAvailable(const char* s)
                :std::logic_error(s) {
        };

        /**
         * @brief Constructor
         * @param s text description of the exception
         */
        explicit ResourceNotAvailable(const std::string& s)
                :std::logic_error(s) {
        };
    };

}

#endif //KAMI_ERROR_H
