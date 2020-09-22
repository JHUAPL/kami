/*-
 * TODO FILEHEADER
 */

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/kami.hpp>
#include <kami/grid.hpp>
#include <kami/multigrid2d.hpp>
#include <map>
#include <mutex>
#include <vector>

namespace kami {

MultiGrid2DCoord::MultiGrid2DCoord(int newXCoord, int newYCoord) {
    xCoord = newXCoord;
    yCoord = newYCoord;
}

int MultiGrid2DCoord::getXCoord(void) const {
    return xCoord;
}

int MultiGrid2DCoord::getYCoord(void) const {
    return yCoord;
}

bool operator==(const MultiGrid2DCoord &lhs, const MultiGrid2DCoord &rhs) {
    return (lhs.xCoord == rhs.yCoord && lhs.yCoord == rhs.yCoord);
}

bool operator!=(const MultiGrid2DCoord &lhs, const MultiGrid2DCoord &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &lhs, const MultiGrid2DCoord &rhs) {
    return lhs << "(" << rhs.xCoord << ", " << rhs.yCoord << ")";
}

MultiGrid2D::MultiGrid2D(unsigned int newMaxCols, unsigned int newMaxRows, bool newColWrap = false, bool newRowWrap = false) {
    setMaxCols(newMaxCols);
    setMaxRows(newMaxRows);

    setColWrap(newColWrap);
    setRowWrap(newRowWrap);

    agentGrid = new std::vector<AgentID> *[newMaxCols];
    for (unsigned int i = 0; i < newMaxRows; i++)
        agentGrid[i] = new std::vector<AgentID>[newMaxRows];

    agentIndex = new std::map<AgentID, MultiGrid2DCoord>;
}

MultiGrid2D::~MultiGrid2D(void) {
    delete agentIndex;

    for (unsigned int i = 0; i < maxRows; i++)
        delete[] agentGrid[i];
    delete[] agentGrid;
}

bool MultiGrid2D::addAgent(AgentID agentID, int xCoord, int yCoord) {
    return addAgent(agentID, MultiGrid2DCoord(xCoord, yCoord));
}
bool MultiGrid2D::addAgent(AgentID agentID, MultiGrid2DCoord location) {
    if (isLocationValid(location)) {
        agentIndex->insert(std::pair<AgentID, MultiGrid2DCoord>(agentID, location));
        agentGrid[location.getXCoord()][location.getYCoord()].push_back(agentID);
        return (true);
    }

    return (false);
}

void MultiGrid2D::deleteAgent(AgentID agentID) {
    MultiGrid2DCoord location = getLocationByAgent(agentID);

    deleteAgent(agentID, location);
}

void MultiGrid2D::deleteAgent(AgentID agentID, int xCoord, int yCoord) {
    deleteAgent(agentID, MultiGrid2DCoord(xCoord, yCoord));
}

void MultiGrid2D::deleteAgent(AgentID agentID, MultiGrid2DCoord location) {
    auto agentList = agentGrid[static_cast<int>(location.getXCoord())][static_cast<int>(location.getYCoord())];
    for (auto testAgentID = agentList.begin(); testAgentID < agentList.end(); testAgentID++) {
        if (*testAgentID == agentID) {
            agentList.erase(testAgentID);
            agentIndex->erase(agentID);
        }
    }
}

bool MultiGrid2D::isLocationValid(MultiGrid2DCoord location) const {
    auto xCoord = location.getXCoord();
    auto yCoord = location.getYCoord();

    return (xCoord >= 0 && xCoord < static_cast<int>(maxCols) && yCoord >= 0 && yCoord < static_cast<int>(maxRows));
}

MultiGrid2DCoord MultiGrid2D::getLocationByAgent(AgentID agentID) const {
    return agentIndex->at(agentID);
}

void MultiGrid2D::moveAgent(AgentID agentID, MultiGrid2DCoord nextLocation) {
    MultiGrid2DCoord currLocation = getLocationByAgent(agentID);

    deleteAgent(agentID, currLocation);
    addAgent(agentID, nextLocation);
}

void MultiGrid2D::setColWrap(bool newColWrap) { colWrap = newColWrap; }
void MultiGrid2D::setRowWrap(bool newRowWrap) { rowWrap = newRowWrap; }
bool MultiGrid2D::getColWrap(void) const { return colWrap; }
bool MultiGrid2D::getRowWrap(void) const { return rowWrap; }

std::vector<MultiGrid2DCoord> MultiGrid2D::getNeighborhood(AgentID agentID, GridNeighborhoodType nType, bool includeCenter) const {
    MultiGrid2DCoord location = getLocationByAgent(agentID);

    return getNeighborhood(location, nType, includeCenter);
}

std::vector<MultiGrid2DCoord> MultiGrid2D::getNeighborhood(MultiGrid2DCoord location, GridNeighborhoodType nType, bool includeCenter) const {
    std::vector<MultiGrid2DCoord> neighborhood;
    auto xCoord = location.getXCoord();
    auto yCoord = location.getYCoord();

    if (includeCenter == true)
        neighborhood.push_back(location);

    // N, E, S, W
    neighborhood.push_back(locationWrap(xCoord, yCoord - 1));
    neighborhood.push_back(locationWrap(xCoord + 1, yCoord));
    neighborhood.push_back(locationWrap(xCoord, yCoord + 1));
    neighborhood.push_back(locationWrap(xCoord - 1, yCoord));

    if (nType == GridNeighborhoodType::Moore) {
        // NE, SE, SW, NW
        neighborhood.push_back(locationWrap(xCoord + 1, yCoord - 1));
        neighborhood.push_back(locationWrap(xCoord + 1, yCoord + 1));
        neighborhood.push_back(locationWrap(xCoord - 1, yCoord + 1));
        neighborhood.push_back(locationWrap(xCoord - 1, yCoord - 1));
    }

    return neighborhood;
}

std::vector<AgentID> *MultiGrid2D::getCellContents(MultiGrid2DCoord location) {
    if (isLocationValid(location)) {
        return &agentGrid[location.getXCoord()][location.getYCoord()];
    }

    return nullptr;
}

void MultiGrid2D::setMaxCols(unsigned int newMaxCols) { maxCols = newMaxCols; }
void MultiGrid2D::setMaxRows(unsigned int newMaxRows) { maxRows = newMaxRows; }
unsigned int MultiGrid2D::getMaxCols(void) const { return maxCols; }
unsigned int MultiGrid2D::getMaxRows(void) const { return maxRows; }

MultiGrid2DCoord MultiGrid2D::locationWrap(MultiGrid2DCoord location) const {
    return locationWrap(location.getXCoord(), location.getYCoord());
}

MultiGrid2DCoord MultiGrid2D::locationWrap(int xCoord, int yCoord) const {
    if (colWrap == true)
        xCoord = (xCoord + static_cast<int>(maxCols)) % static_cast<int>(maxCols);
    if (rowWrap == true)
        yCoord = (yCoord + static_cast<int>(maxRows)) % static_cast<int>(maxRows);
    return MultiGrid2DCoord(xCoord, yCoord);
}

}  // namespace kami
