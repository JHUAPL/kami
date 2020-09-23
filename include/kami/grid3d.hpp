/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_GRID3D_HPP
#define KAMI_GRID3D_HPP

#include <iostream>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/kami.hpp>
#include <map>
#include <vector>

namespace kami {

class GridCoord3D : public GridCoord {
   public:
    GridCoord3D(int, int, int);

    int getX(void) const;
    int getY(void) const;
    int getZ(void) const;

    friend bool operator==(const GridCoord3D &, const GridCoord3D &);
    friend bool operator!=(const GridCoord3D &, const GridCoord3D &);
    friend std::ostream &operator<<(std::ostream &, const GridCoord3D &);

   private:
    int x, y, z;
};

class Grid3D : public GridDomain {
   public:
    Grid3D(unsigned int, unsigned int, unsigned int, bool, bool, bool);
    virtual ~Grid3D();

    bool addAgent(AgentID, int, int, int);
    virtual bool addAgent(AgentID, GridCoord3D) = 0;

    bool deleteAgent(AgentID);
    bool deleteAgent(AgentID, int, int, int);
    bool deleteAgent(AgentID, GridCoord3D);

    bool moveAgent(AgentID, GridCoord3D);

    bool isEmpty(GridCoord3D) const;
    bool isLocationValid(GridCoord3D) const;

    GridCoord3D getLocationByAgent(AgentID) const;
    std::vector<AgentID> *getCellContents(GridCoord3D) const;

    void setWrapX(bool);
    void setWrapY(bool);
    void setWrapZ(bool);
    bool getWrapX(void) const;
    bool getWrapY(void) const;
    bool getWrapZ(void) const;

    std::vector<GridCoord3D> getNeighborhood(AgentID, GridNeighborhoodType, bool) const;
    std::vector<GridCoord3D> getNeighborhood(GridCoord3D, GridNeighborhoodType, bool) const;

    unsigned int getMaxX(void) const;
    unsigned int getMaxY(void) const;
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

#endif  // KAMI_GRID3D_HPP
