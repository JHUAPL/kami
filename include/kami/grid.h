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
#ifndef KAMI_GRID_H
//! @cond SuppressGuard
#define KAMI_GRID_H
//! @endcond

#include <string>

#include <kami/domain.h>
#include <kami/kami.h>

namespace kami {

    /**
     * @brief Neighborhood types for orthogonal grid domains of cells.
     *
     * @details Orthogonal grid domains are those that provide cells equidistant
     * along a standard Cartesian grid.  `GridNeighborhoodType` allows for the
     * distinction between those neighborhoods that include those cells touching on
     * the corners or diagonally and those neighborhoods that do not.
     */
    enum class GridNeighborhoodType {
        /**
         * @brief Moore neighborhood
         *
         * @details Moore neighborhood types include diagonally-adjacent cells as
         * neighbors.
         */
        Moore,

        /**
         * @brief Von Neumann neighborhood
         *
         * @details Von Neumann neighborhood types do not include
         * diagonally-adjacent cells as neighbors.
         */
        VonNeumann
    };

    /**
     * @brief Distance types for orthogonal grid domains
     */
    enum class GridDistanceType {
        /**
         * @brief Euclidean distance.
         *
         * @details The Euclidean distance is the length of the line segment
         * connecting two points.  This is commonly called a "beeline" or
         * "as the crow flies."
         */
        Euclidean,

        /**
         * @brief Manhattan distance.
         *
         * @details The Manhattan distance is the sum of the absolute value of the
         * differences of the elements. This is commonly called the
         * "taxicab distance," "rectilinear distance," or many other [formal
         * names](https://en.wikipedia.org/wiki/Taxicab_geometry).
         */
        Manhattan,

        /**
         * @brief Chebyshev distance.
         *
         * @details The Chebyshev distance, also called the "chessboard" distance
         * is the number of single point jumps necessary to move from one point to
         * the next.  This can be likened to a king on a chessboard and the number
         * of moves necessary to move from a given point to any other given point.
         */
        Chebyshev
    };

    /**
     * @brief An abstract domain based on a gridded environment.
     *
     * @details All gridded domains are expected to consist of cells in a
     * rectilinear grid where the cells are equal size and laid out in an ordered
     * fashion.
     */
    class LIBKAMI_EXPORT GridDomain : public Domain {};

    /**
     * @brief An abstract for gridded coordinates.
     *
     * @details All gridded coordinates are expected to subclass `GridCoord`.
     */
    class LIBKAMI_EXPORT GridCoord : public Coord {

    public:

        /**
         * @brief Find the distance between two points
         *
         * @details Find the distance between two points using the
         * specified metric.  There are three options provided by
         * the `GridDistanceType` class.
         *
         * However, the coordinate class is not aware of the
         * properties of the `GridDomain` it is operating on.  Accordingly,
         * if the direct path is measured, without accounting for
         * and toroidal wrapping of the underlying `GridDomain`.
         *
         * @param p the point to measure the distance to
         * @param distance_type specify the distance type
         *
         * @returns the distance as a `double`
         */
        virtual std::optional<double> distance(std::shared_ptr<Coord> &p, GridDistanceType distance_type) const = 0;

    };

}  // namespace kami

#endif  // KAMI_GRID_H
