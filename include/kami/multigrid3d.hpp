/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_MULTIGRID3D_HPP
#define KAMI_MULTIGRID3D_HPP

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/kami.hpp>
#include <map>
#include <mutex>
#include <vector>

namespace kami {

/// asdfasdf
class MultiGrid3DCoord {
   public:
    MultiGrid3DCoord(int, int, int);

    int getX(void) const;
    int getY(void) const;
    int getZ(void) const;

    friend bool operator==(const MultiGrid3DCoord &, const MultiGrid3DCoord &);
    friend bool operator!=(const MultiGrid3DCoord &, const MultiGrid3DCoord &);
    friend std::ostream &operator<<(std::ostream &, const MultiGrid3DCoord &);

   private:
    int x, y, z;
};

class MultiGrid3D : public GridDomain {
   public:
    MultiGrid3D(unsigned int, unsigned int, unsigned int, bool, bool, bool);
    ~MultiGrid3D(void);

    bool addAgent(AgentID, int, int, int);
    bool addAgent(AgentID, MultiGrid3DCoord);

    void deleteAgent(AgentID);
    void deleteAgent(AgentID, int, int, int);
    void deleteAgent(AgentID, MultiGrid3DCoord);

    bool isLocationValid(MultiGrid3DCoord) const;

    MultiGrid3DCoord getLocationByAgent(AgentID) const;

    void moveAgent(AgentID, MultiGrid3DCoord);

    void setWrapX(bool);
    void setWrapY(bool);
    void setWrapZ(bool);
    bool getWrapX(void) const;
    bool getWrapY(void) const;
    bool getWrapZ(void) const;

    std::vector<MultiGrid3DCoord> getNeighborhood(MultiGrid3DCoord, GridNeighborhoodType, bool) const;
    std::vector<MultiGrid3DCoord> getNeighborhood(AgentID, GridNeighborhoodType, bool) const;

    std::vector<AgentID> *getCellContents(MultiGrid3DCoord);

    unsigned int getMaxX(void) const;
    unsigned int getMaxY(void) const;
    unsigned int getMaxZ(void) const;

   private:
    std::vector<AgentID> ***agentGrid;
    std::map<AgentID, MultiGrid3DCoord> *agentIndex;
    static std::mutex lock;
    unsigned int maxX, maxY, maxZ;
    bool wrapX, wrapY, wrapZ;

    MultiGrid3DCoord locationWrap(int, int, int) const;
    MultiGrid3DCoord locationWrap(MultiGrid3DCoord) const;
};

}  // namespace kami

#endif  // KAMI_MULTIGRID3D_HPP
