/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_GRID2D_HPP
#define KAMI_GRID2D_HPP

#include <iostream>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/kami.hpp>
#include <map>
#include <vector>

namespace kami {

class GridCoord2D : public GridCoord {
   public:
    GridCoord2D(int, int);

    int getX(void) const;
    int getY(void) const;

    friend bool operator==(const GridCoord2D &, const GridCoord2D &);
    friend bool operator!=(const GridCoord2D &, const GridCoord2D &);
    friend std::ostream &operator<<(std::ostream &, const GridCoord2D &);

   private:
    int x, y;
};

class Grid2D : public GridDomain {
   public:
    Grid2D(unsigned int, unsigned int, bool, bool);
    virtual ~Grid2D();

    bool addAgent(AgentID, int, int);
    virtual bool addAgent(AgentID, GridCoord2D) = 0;

    bool deleteAgent(AgentID);
    bool deleteAgent(AgentID, int, int);
    bool deleteAgent(AgentID, GridCoord2D);

    bool moveAgent(AgentID, GridCoord2D);

    bool isEmpty(GridCoord2D) const;
    bool isLocationValid(GridCoord2D) const;

    GridCoord2D getLocationByAgent(AgentID) const;
    std::vector<AgentID> *getCellContents(GridCoord2D) const;

    void setWrapX(bool);
    void setWrapY(bool);
    bool getWrapX(void) const;
    bool getWrapY(void) const;

    std::vector<GridCoord2D> getNeighborhood(AgentID, GridNeighborhoodType, bool) const;
    std::vector<GridCoord2D> getNeighborhood(GridCoord2D, GridNeighborhoodType, bool) const;

    unsigned int getMaxX(void) const;
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

#endif  // KAMI_GRID2D_HPP
