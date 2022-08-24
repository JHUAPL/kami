/*-
 * Copyright (c) 2020 The Johns Hopkins University Applied Physics
 * Laboratory LLC
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#ifndef KAMI_KAMI_H
//! @cond SuppressGuard
#define KAMI_KAMI_H
//! @endcond

#include <semver.hpp>

#include <kami/KAMI_EXPORT.h>
#include <kami/config.h>

namespace kami {

    // Forward declarations to clean up a lot of include-file madness
    class Agent;
    class AgentID;
    class Domain;
    class Model;

    class Population;

    class Scheduler;

    /**
     * @brief Get the current version of Kami
     *
     * @return a `semver::version` object containing version information
     */
    inline semver::version get_version() { return version; }

    /**
     * @brief A catalog of handy constants, mostly useful for seeding
     * a random number generator
     */
    class Constants {
    public:
        /**
         * @brief Life, the Universe, and Everything!
         */
        static constexpr auto ADAMS_CONSTANT = 42u;

        /**
         * @brief Jenny, I've got your number
         */
        static constexpr auto JENNYS_NUMBER = 8675309u;

        /**
         * @brief $(7^(\e - 1/\e) - 9)*\pi^2$
         */
        static constexpr auto JENNYS_CONSTANT = 867.530901989;
    };

}  // namespace kami

#endif  // KAMI_KAMI_H
