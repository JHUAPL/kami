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

MultiGrid1DCoord::MultiGrid1DCoord(int newCoord) {
    coord = newCoord;
}

int MultiGrid1DCoord::getCoord() const {
    return coord;
}

bool operator==(const MultiGrid1DCoord &lhs, const MultiGrid1DCoord &rhs) {
    return (lhs.coord == rhs.coord);
}

bool operator!=(const MultiGrid1DCoord &lhs, const MultiGrid1DCoord &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &lhs, const MultiGrid1DCoord &rhs) {
    return lhs << "(" << rhs.coord << ")";
}

MultiGrid1D::MultiGrid1D(unsigned int newMaxCols, bool newColWrap = false) {
    agentGrid = new std::vector<AgentID>[newMaxCols];
    agentIndex = new std::map<AgentID, MultiGrid1DCoord>;

    maxCols = newMaxCols;
    colWrap = newColWrap;
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
        agentGrid[location.getCoord()].push_back(agentID);
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
    auto agentList = agentGrid[static_cast<int>(location.getCoord())];
    for (auto testAgentID = agentList.begin(); testAgentID < agentList.end(); testAgentID++) {
        if (*testAgentID == agentID) {
            agentList.erase(testAgentID);
            agentIndex->erase(agentID);
        }
    }
}

bool MultiGrid1D::isLocationValid(MultiGrid1DCoord location) const {
    auto coord = location.getCoord();

    return (coord >= 0 && coord < static_cast<int>(maxCols));
}

MultiGrid1DCoord MultiGrid1D::getLocationByAgent(AgentID agentID) const {
    return agentIndex->at(agentID);
}

void MultiGrid1D::moveAgent(AgentID agentID, MultiGrid1DCoord nextLocation) {
    MultiGrid1DCoord currLocation = getLocationByAgent(agentID);

    deleteAgent(agentID, currLocation);
    addAgent(agentID, nextLocation);
}

void MultiGrid1D::setWrap(bool newColWrap) { colWrap = newColWrap; }
bool MultiGrid1D::getWrap(void) const { return colWrap; }

std::vector<MultiGrid1DCoord> MultiGrid1D::getNeighborhood(AgentID agentID, bool includeCenter) const {
    MultiGrid1DCoord location = getLocationByAgent(agentID);

    return getNeighborhood(location, includeCenter);
}

std::vector<MultiGrid1DCoord> MultiGrid1D::getNeighborhood(MultiGrid1DCoord location, bool includeCenter) const {
    std::vector<MultiGrid1DCoord> neighborhood;
    auto coord = location.getCoord();

    if (includeCenter == true)
        neighborhood.push_back(location);

    // E, W
    neighborhood.push_back(locationWrap(coord + 1));
    neighborhood.push_back(locationWrap(coord - 1));

    return neighborhood;
}

std::vector<AgentID> *MultiGrid1D::getCellContents(MultiGrid1DCoord location) {
    if (isLocationValid(location)) {
        return &agentGrid[location.getCoord()];
    }

    return nullptr;
}

void MultiGrid1D::setMaxCols(unsigned int newMaxCols) { maxCols = newMaxCols; }
unsigned int MultiGrid1D::getMaxCols(void) const { return maxCols; }

MultiGrid1DCoord MultiGrid1D::locationWrap(MultiGrid1DCoord location) const {
    return locationWrap(location.getCoord());
}

MultiGrid1DCoord MultiGrid1D::locationWrap(int coord) const {
    if (colWrap == true)
        coord = (coord + static_cast<int>(maxCols)) % static_cast<int>(maxCols);
    return MultiGrid1DCoord(coord);
}

}  // namespace kami
