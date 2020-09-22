/*-
 * TODO FILEHEADER
 */

#include <chrono>
#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/kami.hpp>
#include <kami/multigrid1d.hpp>
#include <map>
#include <mutex>
#include <thread>
#include <vector>

namespace kami {

MultiGrid1DCoord::MultiGrid1DCoord(int newX) {
    x = newX;
}

int MultiGrid1DCoord::getX() const {
    return x;
}

bool operator==(const MultiGrid1DCoord &lhs, const MultiGrid1DCoord &rhs) {
    return (lhs.x == rhs.x);
}

bool operator!=(const MultiGrid1DCoord &lhs, const MultiGrid1DCoord &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &lhs, const MultiGrid1DCoord &rhs) {
    return lhs << "(" << rhs.x << ")";
}

MultiGrid1D::MultiGrid1D(unsigned int newMaxX, bool newWrapX = false) {
    maxX = newMaxX;

    setWrapX(newWrapX);

    agentGrid = new std::vector<AgentID>[maxX];
    agentIndex = new std::map<AgentID, MultiGrid1DCoord>;
}

MultiGrid1D::~MultiGrid1D(void) {
    delete agentIndex;
    delete[] agentGrid;
}

bool MultiGrid1D::addAgent(AgentID agentID, int coord) {
    return addAgent(agentID, MultiGrid1DCoord(coord));
}

bool MultiGrid1D::addAgent(AgentID agentID, MultiGrid1DCoord location) {
    if (isLocationValid(location)) {
        agentIndex->insert(std::pair<AgentID, MultiGrid1DCoord>(agentID, location));
        agentGrid[location.getX()].push_back(agentID);
        return (true);
    }

    return (false);
}

void MultiGrid1D::deleteAgent(AgentID agentID) {
    MultiGrid1DCoord location = getLocationByAgent(agentID);

    deleteAgent(agentID, location);
}

void MultiGrid1D::deleteAgent(AgentID agentID, int coord) {
    deleteAgent(agentID, MultiGrid1DCoord(coord));
}

void MultiGrid1D::deleteAgent(AgentID agentID, MultiGrid1DCoord location) {
    auto agentList = agentGrid[static_cast<int>(location.getX())];
    for (auto testAgentID = agentList.begin(); testAgentID < agentList.end(); testAgentID++) {
        if (*testAgentID == agentID) {
            agentList.erase(testAgentID);
            agentIndex->erase(agentID);
        }
    }
}

bool MultiGrid1D::isLocationValid(MultiGrid1DCoord location) const {
    auto x = location.getX();

    return (x >= 0 && x < static_cast<int>(maxX));
}

MultiGrid1DCoord MultiGrid1D::getLocationByAgent(AgentID agentID) const {
    return agentIndex->at(agentID);
}

void MultiGrid1D::moveAgent(AgentID agentID, MultiGrid1DCoord nextLocation) {
    MultiGrid1DCoord currLocation = getLocationByAgent(agentID);

    deleteAgent(agentID, currLocation);
    addAgent(agentID, nextLocation);
}

void MultiGrid1D::setWrapX(bool newWrapX) { wrapX = newWrapX; }
bool MultiGrid1D::getWrapX(void) const { return wrapX; }

std::vector<MultiGrid1DCoord> MultiGrid1D::getNeighborhood(AgentID agentID, bool includeCenter) const {
    MultiGrid1DCoord location = getLocationByAgent(agentID);

    return getNeighborhood(location, includeCenter);
}

std::vector<MultiGrid1DCoord> MultiGrid1D::getNeighborhood(MultiGrid1DCoord location, bool includeCenter) const {
    std::vector<MultiGrid1DCoord> neighborhood;
    auto x = location.getX();

    if (includeCenter == true)
        neighborhood.push_back(location);

    // E, W
    neighborhood.push_back(locationWrap(x + 1));
    neighborhood.push_back(locationWrap(x - 1));

    return neighborhood;
}

std::vector<AgentID> *MultiGrid1D::getCellContents(MultiGrid1DCoord location) {
    if (isLocationValid(location)) {
        return &agentGrid[location.getX()];
    }

    return nullptr;
}

unsigned int MultiGrid1D::getMaxX(void) const { return maxX; }

MultiGrid1DCoord MultiGrid1D::locationWrap(MultiGrid1DCoord location) const {
    return locationWrap(location.getX());
}

MultiGrid1DCoord MultiGrid1D::locationWrap(int x) const {
    if (wrapX == true)
        x = (x + static_cast<int>(maxX)) % static_cast<int>(maxX);
    return MultiGrid1DCoord(x);
}

}  // namespace kami
