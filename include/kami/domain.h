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
#ifndef KAMI_DOMAIN_H
//! @cond SuppressGuard
#define KAMI_DOMAIN_H
//! @endcond

#include <string>

#include <kami/kami.h>

namespace kami {

    /**
     * @brief Provides an environment for the agents to participate in.
     *
     * @details Implementations of virtual environments are expected to subclass `Domain`.
     */
    class LIBKAMI_EXPORT Domain {
    protected:
        /**
         * @brief Constructor.
         *
         * @details Making this constructor protected makes the class abstract without having
         * to create any virtual functions.
         */
        Domain() = default;
    };

    /**
     * @brief Provides a coordinate system for each `Domain`.
     *
     * @details The coordinate system must be able to produce a human-readable version of the
     * coordinates given.  For instance, an integer grid in two dimensions would
     * provide standard Descartes coordinates like (0, 0) for the origin, or (2, 3)
     * for the position that is two units "up" and three units to the "right" of the
     * origin.  Implementation of a coordinate system is left up to the user, though
     * there are several established systems provided.
     *
     * @see GridCoord
     */
    class LIBKAMI_EXPORT Coord {
    public:
        /**
         * @brief Convert the coordinate to a human-readable string.
         *
         * @return a human-readable form of the `Coord` as `std::string`.
         */
        [[nodiscard]] virtual std::string to_string() const = 0;

        /**
         * @brief Output a `Coord` to the specified output stream
         *
         * @details The form of the output will be the same as that produced by the
         * `to_string()` member function.
         *
         * @param lhs is the stream to output the `Coord` to
         * @param rhs is the `Coord` to output
         * @return the output stream for reuse
         */
        friend std::ostream& operator<<(
                std::ostream& lhs,
                const Coord& rhs
        );
    };

}  // namespace kami

#endif  // KAMI_DOMAIN_H
