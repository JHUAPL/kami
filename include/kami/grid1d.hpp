/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_GRID1D_HPP
#define KAMI_GRID1D_HPP

#include <iostream>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/kami.hpp>
#include <map>
#include <vector>

namespace kami {

class GridCoord1D : public GridCoord {
   public:
    GridCoord1D(int);

    int getX(void) const;

    friend bool operator==(const GridCoord1D &, const GridCoord1D &);
    friend bool operator!=(const GridCoord1D &, const GridCoord1D &);
    friend std::ostream &operator<<(std::ostream &, const GridCoord1D &);

   private:
    int x;
};

class Grid1D : public GridDomain {
   public:
    Grid1D(unsigned int, bool);
    virtual ~Grid1D();

    bool addAgent(AgentID, int);
    virtual bool addAgent(AgentID, GridCoord1D) = 0;

    bool deleteAgent(AgentID);
    bool deleteAgent(AgentID, int);
    bool deleteAgent(AgentID, GridCoord1D);

    bool moveAgent(AgentID, GridCoord1D);

    bool isEmpty(GridCoord1D) const;
    bool isLocationValid(GridCoord1D) const;

    GridCoord1D getLocationByAgent(AgentID) const;
    std::vector<AgentID> *getCellContents(GridCoord1D) const;

    void setWrapX(bool);
    bool getWrapX(void) const;

    std::vector<GridCoord1D> getNeighborhood(AgentID, bool) const;
    std::vector<GridCoord1D> getNeighborhood(GridCoord1D, bool) const;

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
