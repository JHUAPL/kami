/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_GRID1D_HPP
#define KAMI_GRID1D_HPP

#include <iostream>
#include <kami/KAMI_EXPORT.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/kami.hpp>
#include <map>
#include <vector>

namespace kami {

///  \brief Onem-dimensional coordinates.
class KAMI_EXPORT GridCoord1D : public GridCoord {
   public:
    ///  \brief  Constructor for one-dimensional coordinates.
    GridCoord1D(int);

    ///  Get the `X` coordinate.
    int getX(void) const;

    ///  \brief Convert the identifier to a human readable string.
    std::string toString() const;
    
    ///  Test if two coordinates are equal.
    friend bool operator==(const GridCoord1D &, const GridCoord1D &);

    ///  Test if two coordinates are not equal.
    friend bool operator!=(const GridCoord1D &, const GridCoord1D &);

    ///  Output a given coordinate to the specified stream.
    friend std::ostream &operator<<(std::ostream &, const GridCoord1D &);

   private:
    int x;
};

///  \brief A one-dimensional grid where each cell may contain
///  agents.
///
///  \details The grid is linear and may wrap around in either
///  dimension.
class KAMI_EXPORT Grid1D : public GridDomain {
   public:
    ///  Constructor
    Grid1D(unsigned int, bool);

    ///  Deconstructor
    virtual ~Grid1D();

    /// \brief Place agent on the grid at the specified location.
    bool addAgent(AgentID, int);

    /// \brief Place agent on the grid at the specified location.
    virtual bool addAgent(AgentID, GridCoord1D) = 0;

    /// Remove agent from the grid
    bool deleteAgent(AgentID);

    /// Remove agent from the grid
    bool deleteAgent(AgentID, int);

    /// Remove agent from the grid
    bool deleteAgent(AgentID, GridCoord1D);

    ///  Move an agent to the specified location.
    bool moveAgent(AgentID, GridCoord1D);

    ///  Inquire if the specified location is empty.
    bool isEmpty(GridCoord1D) const;

    ///  Inquire if the specified location is valid within the grid.
    bool isLocationValid(GridCoord1D) const;

    ///  Get the location of the specified agent.
    GridCoord1D getLocationByAgent(AgentID) const;

    ///  Get the contents of the specified location.
    std::vector<AgentID> *getCellContents(GridCoord1D) const;

    ///  Set the wrapping in the `X` dimension.
    void setWrapX(bool);

    ///  Inquire to whether the grid wraps in the `X` dimension.
    bool getWrapX(void) const;

    ///  Return the neighborhood of the specified Agent
    std::vector<GridCoord1D> getNeighborhood(AgentID, bool) const;

    ///  Return the neighborhood of the specified Agent
    std::vector<GridCoord1D> getNeighborhood(GridCoord1D, bool) const;

    ///  Get the length of the grid in the `X` dimension.
    unsigned int getMaxX(void) const;

   protected:
    std::vector<AgentID> *agentGrid;
    std::map<AgentID, GridCoord1D> *agentIndex;
    unsigned int maxX;
    bool wrapX;

    GridCoord1D locationWrap(int) const;
    GridCoord1D locationWrap(GridCoord1D) const;

   private:
    void setMaxX(unsigned int);
};

}  // namespace kami

#endif  // KAMI_GRID1D_HPP
