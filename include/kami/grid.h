/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_GRID_H
#define KAMI_GRID_H

#include <iostream>
#include <kami/KAMI_EXPORT.h>
#include <kami/domain.h>
#include <kami/kami.h>

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
enum LIBKAMI_EXPORT GridDistanceType { Linear,
                                    Taxicab };

///  \brief An abstract domain based on a grid with integer steps
class LIBKAMI_EXPORT GridDomain : public Domain {
};

///  \brief An abstract for integer coordinates
class LIBKAMI_EXPORT GridCoord : public Coord {
};

}  // namespace kami

#endif  // KAMI_DOMAIN_H
