/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_GRID3D_H
#define KAMI_GRID3D_H

#include <iostream>
#include <kami/KAMI_EXPORT.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/kami.h>
#include <map>
#include <vector>

namespace kami {

///  \brief Three-dimensional coordinates.
class LIBKAMI_EXPORT GridCoord3D : public GridCoord {
   public:
    ///  \brief  Constructor for three-dimensional coordinates.
    GridCoord3D(int, int, int);

    ///  Get the `X` coordinate.
    int getX(void) const;

    ///  Get the `Y` coordinate.
    int getY(void) const;

    ///  Get the `Z` coordinate.
    int getZ(void) const;

    ///  \brief Convert the identifier to a human readable string.
    std::string toString() const;

    ///  Test if two coordinates are equal.
    friend bool operator==(const GridCoord3D &, const GridCoord3D &);

    ///  Test if two coordinates are not equal.
    friend bool operator!=(const GridCoord3D &, const GridCoord3D &);

    ///  Output a given coordinate to the specified stream.
    friend std::ostream &operator<<(std::ostream &, const GridCoord3D &);

   private:
    int x, y, z;
};

///  \brief A three-dimensional grid where each cell may contain
///  agents.
///
///  \details The grid is rectangular and may wrap around in any
///  dimension.
class LIBKAMI_EXPORT Grid3D : public GridDomain {
   public:
    ///  Constructor
    Grid3D(unsigned int, unsigned int, unsigned int, bool, bool, bool);

    ///  Deconstructor
    virtual ~Grid3D();

    /// \brief Place agent on the grid at the specified location.
    bool addAgent(AgentID, int, int, int);

    /// \brief Place agent on the grid at the specified location.
    virtual bool addAgent(AgentID, GridCoord3D) = 0;

    /// Remove agent from the grid
    bool deleteAgent(AgentID);

    /// Remove agent from the grid
    bool deleteAgent(AgentID, int, int, int);

    /// Remove agent from the grid
    bool deleteAgent(AgentID, GridCoord3D);

    ///  Move an agent to the specified location.
    bool moveAgent(AgentID, GridCoord3D);

    ///  Inquire if the specified location is empty.
    bool isEmpty(GridCoord3D) const;

    ///  Inquire if the specified location is valid within the grid.
    bool isLocationValid(GridCoord3D) const;

    ///  Get the location of the specified agent.
    GridCoord3D getLocationByAgent(AgentID) const;

    ///  Get the contents of the specified location.
    std::vector<AgentID> *getCellContents(GridCoord3D) const;

    ///  Set the wrapping in the `X` dimension.
    void setWrapX(bool);
    ///  Set the wrapping in the `Y` dimension.
    void setWrapY(bool);
    ///  Set the wrapping in the `Z` dimension.
    void setWrapZ(bool);

    ///  Inquire to whether the grid wraps in the `X` dimension.
    bool getWrapX(void) const;

    ///  Inquire to whether the grid wraps in the `Y` dimension.
    bool getWrapY(void) const;

    ///  Inquire to whether the grid wraps in the `Z` dimension.
    bool getWrapZ(void) const;

    ///  Return the neighborhood of the specified Agent
    std::vector<GridCoord3D> getNeighborhood(AgentID, GridNeighborhoodType, bool) const;

    ///  Return the neighborhood of the specified cell
    std::vector<GridCoord3D> getNeighborhood(GridCoord3D, GridNeighborhoodType, bool) const;

    ///  Get the length of the grid in the `X` dimension.
    unsigned int getMaxX(void) const;

    ///  Get the length of the grid in the `Y` dimension.
    unsigned int getMaxY(void) const;

    ///  Get the length of the grid in the `Z` dimension.
    unsigned int getMaxZ(void) const;

   protected:
    std::vector<AgentID> ***agentGrid;
    std::map<AgentID, GridCoord3D> *agentIndex;
    unsigned int maxX, maxY, maxZ;
    bool wrapX, wrapY, wrapZ;

    GridCoord3D locationWrap(int, int, int) const;
    GridCoord3D locationWrap(GridCoord3D) const;

   private:
    void setMaxX(unsigned int);
    void setMaxY(unsigned int);
    void setMaxZ(unsigned int);
};

}  // namespace kami

#endif  // KAMI_GRID3D_H
