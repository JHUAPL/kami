/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_MULTIGRID1D_HPP
#define KAMI_MULTIGRID1D_HPP

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/kami.hpp>
#include <map>
#include <mutex>
#include <vector>

namespace kami {

/// asdfasdf
class MultiGrid1DCoord {
   public:
    MultiGrid1DCoord(int);

    int getCoord(void) const;

    friend bool operator==(const MultiGrid1DCoord &, const MultiGrid1DCoord &);
    friend bool operator!=(const MultiGrid1DCoord &, const MultiGrid1DCoord &);
    friend std::ostream &operator<<(std::ostream &, const MultiGrid1DCoord &);

   private:
    int coord;
};

class MultiGrid1D : public GridDomain {
   public:
    MultiGrid1D(unsigned int, bool);
    ~MultiGrid1D(void);

    bool addAgent(AgentID, int);
    bool addAgent(AgentID, MultiGrid1DCoord);

    void deleteAgent(AgentID);
    void deleteAgent(AgentID, int);
    void deleteAgent(AgentID, MultiGrid1DCoord);

    bool isLocationValid(MultiGrid1DCoord) const;

    MultiGrid1DCoord getLocationByAgent(AgentID) const;

    void moveAgent(AgentID, MultiGrid1DCoord);

    void setWrap(bool);
    bool getWrap(void) const;

    std::vector<MultiGrid1DCoord> getNeighborhood(MultiGrid1DCoord, bool) const;
    std::vector<MultiGrid1DCoord> getNeighborhood(AgentID, bool) const;

    std::vector<AgentID> *getCellContents(MultiGrid1DCoord);

    void setMaxCols(unsigned int);
    unsigned int getMaxCols(void) const;

   private:
    std::vector<AgentID> *agentGrid;
    std::map<AgentID, MultiGrid1DCoord> *agentIndex;
    static std::mutex lock;
    unsigned int maxCols;
    bool colWrap;

    MultiGrid1DCoord locationWrap(int) const;
    MultiGrid1DCoord locationWrap(MultiGrid1DCoord) const;
};

}  // namespace kami

#endif  // KAMI_MULTIGRID1D_HPP
