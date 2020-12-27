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
#define KAMI_GRID_H

#include <kami/KAMI_EXPORT.h>
#include <kami/domain.h>
#include <kami/kami.h>

#include <string>

namespace kami {

///  \brief Neighborhood types for orthogonal grid domains
enum LIBKAMI_EXPORT GridNeighborhoodType {
    ///  \brief Moore neighborhood.
    ///  \details Moore neighborhood types include diagonally
    ///  adjacent cells as neighbors.
    Moore,

    ///  \brief Von Neumann neighborhood.
    ///  \details Von Neumann neighborhood types do not include
    ///  diagonally adjacent cells as neighbors.
    VonNeumann
};

///  \brief Distance types for orthogonal grid domains
enum LIBKAMI_EXPORT GridDistanceType {
    ///  \brief Euclidean distance
    ///  \details The Euclidean distance is the length of the line segment
    ///  connecting two points.
    Euclidean,

    ///  \brief Manhattan distance
    ///  \details The Manhattan distance is the sum of the absolute values
    ///  differences of the elements.
    Manhattan
};

///  \brief An abstract domain based on a grid with integer steps
class LIBKAMI_EXPORT GridDomain : public Domain {};

///  \brief An abstract for integer coordinates
class LIBKAMI_EXPORT GridCoord : public Coord {
   public:
    std::string to_string() const { return std::string(); };
};

}  // namespace kami

#endif  // KAMI_DOMAIN_H
