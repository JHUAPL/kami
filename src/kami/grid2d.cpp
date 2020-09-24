/*-
 * TODO FILEHEADER
 */

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/grid2d.hpp>
#include <kami/kami.hpp>
#include <map>
#include <vector>

namespace kami {

GridCoord2D::GridCoord2D(int newX, int newY) {
    x = newX;
    y = newY;
}

int GridCoord2D::getX(void) const {
    return x;
}

int GridCoord2D::getY(void) const {
    return y;
}

bool operator==(const GridCoord2D &lhs, const GridCoord2D &rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator!=(const GridCoord2D &lhs, const GridCoord2D &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &lhs, const GridCoord2D &rhs) {
    return lhs << "(" << rhs.x << ", " << rhs.y << ")";
}

Grid2D::Grid2D(unsigned int newMaxX, unsigned int newMaxY, bool newWrapX = false, bool newWrapY = false) {
    setMaxX(newMaxX);
    setMaxY(newMaxY);

    setWrapX(newWrapX);
    setWrapY(newWrapY);

    agentGrid = new std::vector<AgentID> *[maxX];
    for (unsigned int i = 0; i < maxX; i++)
        agentGrid[i] = new std::vector<AgentID>[maxY];

    agentIndex = new std::map<AgentID, GridCoord2D>;
}

Grid2D::~Grid2D(void) {
    delete agentIndex;

    for (unsigned int i = 0; i < maxX; i++)
        delete[] agentGrid[i];
    delete[] agentGrid;
}

bool Grid2D::addAgent(AgentID agentID, int x, int y) {
    return addAgent(agentID, GridCoord2D(x, y));
}

bool Grid2D::deleteAgent(AgentID agentID) {
    GridCoord2D location = getLocationByAgent(agentID);

    return deleteAgent(agentID, location);
}

bool Grid2D::deleteAgent(AgentID agentID, int x, int y) {
    return deleteAgent(agentID, GridCoord2D(x, y));
}

bool Grid2D::deleteAgent(AgentID agentID, GridCoord2D location) {
    auto agentList = agentGrid[static_cast<int>(location.getX())][static_cast<int>(location.getY())];
    for (auto testAgentID = agentList.begin(); testAgentID < agentList.end(); testAgentID++) {
        if (*testAgentID == agentID) {
            agentList.erase(testAgentID);
            agentIndex->erase(agentID);
            return true;
        }
    }

    return false;
}

bool Grid2D::isLocationValid(GridCoord2D location) const {
    auto x = location.getX();
    auto y = location.getY();

    return (x >= 0 && x < static_cast<int>(maxX) &&
            y >= 0 && y < static_cast<int>(maxY));
}

GridCoord2D Grid2D::getLocationByAgent(AgentID agentID) const {
    return agentIndex->at(agentID);
}

bool Grid2D::moveAgent(AgentID agentID, GridCoord2D nextLocation) {
    GridCoord2D currLocation = getLocationByAgent(agentID);

    if (deleteAgent(agentID, currLocation) == true)
        return addAgent(agentID, nextLocation);
    return false;
}

void Grid2D::setWrapX(bool newWrapX) { wrapX = newWrapX; }
void Grid2D::setWrapY(bool newWrapY) { wrapY = newWrapY; }
bool Grid2D::getWrapX(void) const { return wrapX; }
bool Grid2D::getWrapY(void) const { return wrapY; }

void Grid2D::setMaxX(unsigned int newMaxX) {
    maxX = newMaxX;
}

void Grid2D::setMaxY(unsigned int newMaxY) {
    maxY = newMaxY;
}

std::vector<GridCoord2D> Grid2D::getNeighborhood(AgentID agentID, GridNeighborhoodType nType, bool includeCenter) const {
    GridCoord2D location = getLocationByAgent(agentID);

    return getNeighborhood(location, nType, includeCenter);
}

std::vector<GridCoord2D> Grid2D::getNeighborhood(GridCoord2D location, GridNeighborhoodType nType, bool includeCenter) const {
    std::vector<GridCoord2D> neighborhood;
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

std::vector<AgentID> *Grid2D::getCellContents(GridCoord2D location) const {
    if (isLocationValid(location)) {
        return &agentGrid[location.getX()][location.getY()];
    }

    return nullptr;
}

unsigned int Grid2D::getMaxX(void) const { return maxX; }
unsigned int Grid2D::getMaxY(void) const { return maxY; }

GridCoord2D Grid2D::locationWrap(GridCoord2D location) const {
    return locationWrap(location.getX(), location.getY());
}

GridCoord2D Grid2D::locationWrap(int x, int y) const {
    if (wrapX == true)
        x = (x + static_cast<int>(maxX)) % static_cast<int>(maxX);
    if (wrapY == true)
        y = (y + static_cast<int>(maxY)) % static_cast<int>(maxY);
    return GridCoord2D(x, y);
}

bool Grid2D::isEmpty(GridCoord2D location) const {
    auto x = location.getX();
    auto y = location.getY();

    return agentGrid[x][y].size() == 0;
}
}
