/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_MULTIGRID2D_HPP
#define KAMI_MULTIGRID2D_HPP

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/kami.hpp>
#include <map>
#include <mutex>
#include <vector>

namespace kami {

/// asdfasdf
class MultiGrid2DCoord {
   public:
    MultiGrid2DCoord(int, int);

    int getX(void) const;
    int getY(void) const;

    friend bool operator==(const MultiGrid2DCoord &, const MultiGrid2DCoord &);
    friend bool operator!=(const MultiGrid2DCoord &, const MultiGrid2DCoord &);
    friend std::ostream &operator<<(std::ostream &, const MultiGrid2DCoord &);

   private:
    int x, y;
};

class MultiGrid2D : public GridDomain {
   public:
    MultiGrid2D(unsigned int, unsigned int, bool, bool);
    ~MultiGrid2D(void);

    bool addAgent(AgentID, int, int);
    bool addAgent(AgentID, MultiGrid2DCoord);

    void deleteAgent(AgentID);
    void deleteAgent(AgentID, int, int);
    void deleteAgent(AgentID, MultiGrid2DCoord);

    bool isLocationValid(MultiGrid2DCoord) const;

    MultiGrid2DCoord getLocationByAgent(AgentID) const;

    void moveAgent(AgentID, MultiGrid2DCoord);

    void setWrapX(bool);
    void setWrapY(bool);
    bool getWrapX(void) const;
    bool getWrapY(void) const;

    std::vector<MultiGrid2DCoord> getNeighborhood(MultiGrid2DCoord, GridNeighborhoodType, bool) const;
    std::vector<MultiGrid2DCoord> getNeighborhood(AgentID, GridNeighborhoodType, bool) const;

    std::vector<AgentID> *getCellContents(MultiGrid2DCoord);

    unsigned int getMaxX(void) const;
    unsigned int getMaxY(void) const;

   private:
    std::vector<AgentID> **agentGrid;
    std::map<AgentID, MultiGrid2DCoord> *agentIndex;
    static std::mutex lock;
    unsigned int maxX, maxY;
    bool wrapX, wrapY;

    MultiGrid2DCoord locationWrap(int, int) const;
    MultiGrid2DCoord locationWrap(MultiGrid2DCoord) const;
};

}  // namespace kami

#endif  // KAMI_MULTIGRID2D_HPP
