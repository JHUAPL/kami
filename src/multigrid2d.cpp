/*-
 * TODO FILEHEADER
 */

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/kami.hpp>
#include <kami/multigrid2d.hpp>
#include <map>
#include <mutex>
#include <vector>

namespace kami {

MultiGrid2DCoord::MultiGrid2DCoord(int newX, int newY) {
    x = newX;
    y = newY;
}

int MultiGrid2DCoord::getX(void) const {
    return x;
}

int MultiGrid2DCoord::getY(void) const {
    return y;
}

bool operator==(const MultiGrid2DCoord &lhs, const MultiGrid2DCoord &rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator!=(const MultiGrid2DCoord &lhs, const MultiGrid2DCoord &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &lhs, const MultiGrid2DCoord &rhs) {
    return lhs << "(" << rhs.x << ", " << rhs.y << ")";
}

MultiGrid2D::MultiGrid2D(unsigned int newMaxX, unsigned int newMaxY, bool newWrapX = false, bool newWrapY = false) {
    maxX = newMaxX;
    maxY = newMaxY;

    setWrapX(newWrapX);
    setWrapY(newWrapY);

    agentGrid = new std::vector<AgentID> *[maxX];
    for (unsigned int i = 0; i < maxX; i++)
        agentGrid[i] = new std::vector<AgentID>[maxY];

    agentIndex = new std::map<AgentID, MultiGrid2DCoord>;
}

MultiGrid2D::~MultiGrid2D(void) {
    delete agentIndex;

    for (unsigned int i = 0; i < maxX; i++)
        delete[] agentGrid[i];
    delete[] agentGrid;
}

bool MultiGrid2D::addAgent(AgentID agentID, int x, int y) {
    return addAgent(agentID, MultiGrid2DCoord(x, y));
}
bool MultiGrid2D::addAgent(AgentID agentID, MultiGrid2DCoord location) {
    if (isLocationValid(location)) {
        agentIndex->insert(std::pair<AgentID, MultiGrid2DCoord>(agentID, location));
        agentGrid[location.getX()][location.getY()].push_back(agentID);
        return (true);
    }

    return (false);
}

void MultiGrid2D::deleteAgent(AgentID agentID) {
    MultiGrid2DCoord location = getLocationByAgent(agentID);

    deleteAgent(agentID, location);
}

void MultiGrid2D::deleteAgent(AgentID agentID, int x, int y) {
    deleteAgent(agentID, MultiGrid2DCoord(x, y));
}

void MultiGrid2D::deleteAgent(AgentID agentID, MultiGrid2DCoord location) {
    auto agentList = agentGrid[static_cast<int>(location.getX())][static_cast<int>(location.getY())];
    for (auto testAgentID = agentList.begin(); testAgentID < agentList.end(); testAgentID++) {
        if (*testAgentID == agentID) {
            agentList.erase(testAgentID);
            agentIndex->erase(agentID);
        }
    }
}

bool MultiGrid2D::isLocationValid(MultiGrid2DCoord location) const {
    auto x = location.getX();
    auto y = location.getY();

    return (x >= 0 && x < static_cast<int>(maxX) &&
            y >= 0 && y < static_cast<int>(maxY));
}

MultiGrid2DCoord MultiGrid2D::getLocationByAgent(AgentID agentID) const {
    return agentIndex->at(agentID);
}

void MultiGrid2D::moveAgent(AgentID agentID, MultiGrid2DCoord nextLocation) {
    MultiGrid2DCoord currLocation = getLocationByAgent(agentID);

    deleteAgent(agentID, currLocation);
    addAgent(agentID, nextLocation);
}

void MultiGrid2D::setWrapX(bool newWrapX) { wrapX = newWrapX; }
void MultiGrid2D::setWrapY(bool newWrapY) { wrapY = newWrapY; }
bool MultiGrid2D::getWrapX(void) const { return wrapX; }
bool MultiGrid2D::getWrapY(void) const { return wrapY; }

std::vector<MultiGrid2DCoord> MultiGrid2D::getNeighborhood(AgentID agentID, GridNeighborhoodType nType, bool includeCenter) const {
    MultiGrid2DCoord location = getLocationByAgent(agentID);

    return getNeighborhood(location, nType, includeCenter);
}

std::vector<MultiGrid2DCoord> MultiGrid2D::getNeighborhood(MultiGrid2DCoord location, GridNeighborhoodType nType, bool includeCenter) const {
    std::vector<MultiGrid2DCoord> neighborhood;
    auto x = location.getX();
    auto y = location.getY();

    if (includeCenter == true)
        neighborhood.push_back(location);

    // N, E, S, W
    neighborhood.push_back(locationWrap(x, y - 1));
    neighborhood.push_back(locationWrap(x, y + 1));
    neighborhood.push_back(locationWrap(x + 1, y));
    neighborhood.push_back(locationWrap(x - 1, y));

    if (nType == GridNeighborhoodType::Moore) {
        // NE, SE, SW, NW
        neighborhood.push_back(locationWrap(x + 1, y - 1));
        neighborhood.push_back(locationWrap(x + 1, y + 1));
        neighborhood.push_back(locationWrap(x - 1, y + 1));
        neighborhood.push_back(locationWrap(x - 1, y - 1));
    }

    return neighborhood;
}

std::vector<AgentID> *MultiGrid2D::getCellContents(MultiGrid2DCoord location) {
    if (isLocationValid(location)) {
        return &agentGrid[location.getX()][location.getY()];
    }

    return nullptr;
}

unsigned int MultiGrid2D::getMaxX(void) const { return maxX; }
unsigned int MultiGrid2D::getMaxY(void) const { return maxY; }

MultiGrid2DCoord MultiGrid2D::locationWrap(MultiGrid2DCoord location) const {
    return locationWrap(location.getX(), location.getY());
}

MultiGrid2DCoord MultiGrid2D::locationWrap(int x, int y) const {
    if (wrapX == true)
        x = (x + static_cast<int>(maxX)) % static_cast<int>(maxX);
    if (wrapY == true)
        y = (y + static_cast<int>(maxY)) % static_cast<int>(maxY);
    return MultiGrid2DCoord(x, y);
}

}  // namespace kami
