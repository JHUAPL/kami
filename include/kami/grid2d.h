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
#ifndef KAMI_GRID2D_H
#define KAMI_GRID2D_H

#include <iostream>
#include <kami/KAMI_EXPORT.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/kami.h>
#include <map>
#include <vector>

namespace kami {

///  \brief Two-dimensional coordinates.
class LIBKAMI_EXPORT GridCoord2D : public GridCoord {
   public:
    ///  \brief  Constructor for two-dimensional coordinates.
    GridCoord2D(int, int);

    ///  Get the `X` coordinate.
    int getX(void) const;

    ///  Get the `Y` coordinate.
    int getY(void) const;

    ///  \brief Convert the identifier to a human readable string.
    std::string toString() const;

    ///  Test if two coordinates are equal.
    friend bool operator==(const GridCoord2D &, const GridCoord2D &);

    ///  Test if two coordinates are not equal.
    friend bool operator!=(const GridCoord2D &, const GridCoord2D &);

    ///  Output a given coordinate to the specified stream.
    friend std::ostream &operator<<(std::ostream &, const GridCoord2D &);

   private:
    int x, y;
};

///  \brief A two-dimensional grid where each cell may contain
///  agents.
///
///  \details The grid is rectangular and may wrap around in either
///  dimension.
class LIBKAMI_EXPORT Grid2D : public GridDomain {
   public:
    ///  Constructor
    Grid2D(unsigned int, unsigned int, bool, bool);

    ///  Deconstructor
    virtual ~Grid2D();

    /// \brief Place agent on the grid at the specified location.
    bool addAgent(AgentID, int, int);

    /// \brief Place agent on the grid at the specified location.
    virtual bool addAgent(AgentID, GridCoord2D) = 0;

    /// Remove agent from the grid
    bool deleteAgent(AgentID);

    /// Remove agent from the grid
    bool deleteAgent(AgentID, int, int);

    /// Remove agent from the grid
    bool deleteAgent(AgentID, GridCoord2D);

    ///  Move an agent to the specified location.
    bool moveAgent(AgentID, GridCoord2D);

    ///  Inquire if the specified location is empty.
    bool isEmpty(GridCoord2D) const;

    ///  Inquire if the specified location is valid within the grid.
    bool isLocationValid(GridCoord2D) const;

    ///  Get the location of the specified agent.
    GridCoord2D getLocationByAgent(AgentID) const;

    ///  Get the contents of the specified location.
    std::vector<AgentID> *getCellContents(GridCoord2D) const;

    ///  Set the wrapping in the `X` dimension.
    void setWrapX(bool);

    ///  Set the wrapping in the `Y` dimension.
    void setWrapY(bool);

    ///  Inquire to whether the grid wraps in the `X` dimension.
    bool getWrapX(void) const;

    ///  Inquire to whether the grid wraps in the `Y` dimension.
    bool getWrapY(void) const;

    ///  Return the neighborhood of the specified Agent
    std::vector<GridCoord2D> getNeighborhood(AgentID, GridNeighborhoodType, bool) const;

    ///  Return the neighborhood of the specified cell
    std::vector<GridCoord2D> getNeighborhood(GridCoord2D, GridNeighborhoodType, bool) const;

    ///  Get the length of the grid in the `X` dimension.
    unsigned int getMaxX(void) const;

    ///  Get the length of the grid in the `Y` dimension.
    unsigned int getMaxY(void) const;

   protected:
    std::vector<AgentID> **agentGrid;
    std::map<AgentID, GridCoord2D> *agentIndex;
    unsigned int maxX, maxY;
    bool wrapX, wrapY;

    GridCoord2D locationWrap(int, int) const;
    GridCoord2D locationWrap(GridCoord2D) const;

   private:
    void setMaxX(unsigned int);
    void setMaxY(unsigned int);
};

}  // namespace kami

#endif  // KAMI_GRID2D_H
