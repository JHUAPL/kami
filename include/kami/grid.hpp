/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_GRID_HPP
#define KAMI_GRID_HPP

#include <iostream>
#include <kami/domain.hpp>
#include <kami/kami.hpp>

namespace kami {

///  \brief Neighborhood types for orthogonal grid domains
enum GridNeighborhoodType {
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
enum GridDistanceType { Linear,
                        Taxicab };

///  \brief An abstract domain based on a grid with integer steps
class GridDomain : public Domain {
};

///  \brief An abstract for integer coordinates
class GridCoord {
};

}  // namespace kami

#endif  // KAMI_DOMAIN_HPP
