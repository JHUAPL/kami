/*-
 * TODO FILEHEADER
 */

#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/grid3d.h>
#include <kami/kami.h>
#include <map>
#include <vector>

namespace kami {

GridCoord3D::GridCoord3D(int newX, int newY, int newZ) {
    x = newX;
    y = newY;
    z = newZ;
}

int GridCoord3D::getX(void) const {
    return x;
}

int GridCoord3D::getY(void) const {
    return y;
}

int GridCoord3D::getZ(void) const {
    return z;
}

std::string GridCoord3D::toString() const {
    return std::string("(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")");
}

bool operator==(const GridCoord3D &lhs, const GridCoord3D &rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}

bool operator!=(const GridCoord3D &lhs, const GridCoord3D &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &lhs, const GridCoord3D &rhs) {
    return lhs << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
}

Grid3D::Grid3D(unsigned int newMaxX, unsigned int newMaxY, unsigned int newMaxZ,
               bool newWrapX = false, bool newWrapY = false, bool newWrapZ = false) {
    setMaxX(newMaxX);
    setMaxY(newMaxY);
    setMaxZ(newMaxZ);

    setWrapX(newWrapX);
    setWrapY(newWrapY);
    setWrapZ(newWrapZ);

    agentGrid = new std::vector<AgentID> **[maxX];
    for (unsigned int i = 0; i < maxX; i++) {
        agentGrid[i] = new std::vector<AgentID> *[maxY];
        for (unsigned int j = 0; j < maxY; j++)
            agentGrid[i][j] = new std::vector<AgentID>[maxZ];
    }
    agentIndex = new std::map<AgentID, GridCoord3D>;
}

Grid3D::~Grid3D(void) {
    delete agentIndex;

    for (unsigned int i = 0; i < maxX; i++) {
        for (unsigned int j = 0; j < maxY; j++)
            delete[] agentGrid[i][j];
        delete[] agentGrid[i];
    }
    delete[] agentGrid;
}

bool Grid3D::addAgent(AgentID agentID, int x, int y, int z) {
    return addAgent(agentID, GridCoord3D(x, y, z));
}

bool Grid3D::deleteAgent(AgentID agentID) {
    GridCoord3D location = getLocationByAgent(agentID);

    return deleteAgent(agentID, location);
}

bool Grid3D::deleteAgent(AgentID agentID, int x, int y, int z) {
    return deleteAgent(agentID, GridCoord3D(x, y, z));
}

bool Grid3D::deleteAgent(AgentID agentID, GridCoord3D location) {
    auto agentList = agentGrid[static_cast<int>(location.getX())][static_cast<int>(location.getY())][static_cast<int>(location.getZ())];
    for (auto testAgentID = agentList.begin(); testAgentID < agentList.end(); testAgentID++) {
        if (*testAgentID == agentID) {
            agentList.erase(testAgentID);
            agentIndex->erase(agentID);
            return true;
        }
    }

    return false;
}

bool Grid3D::isLocationValid(GridCoord3D location) const {
    auto x = location.getX();
    auto y = location.getY();
    auto z = location.getZ();

    return (x >= 0 && x < static_cast<int>(maxX) &&
            y >= 0 && y < static_cast<int>(maxY) &&
            z >= 0 && z < static_cast<int>(maxZ));
}

GridCoord3D Grid3D::getLocationByAgent(AgentID agentID) const {
    return agentIndex->at(agentID);
}

bool Grid3D::moveAgent(AgentID agentID, GridCoord3D nextLocation) {
    GridCoord3D currLocation = getLocationByAgent(agentID);

    if (deleteAgent(agentID, currLocation) == true)
        return addAgent(agentID, nextLocation);
    return false;
}

void Grid3D::setWrapX(bool newWrapX) { wrapX = newWrapX; }
void Grid3D::setWrapY(bool newWrapY) { wrapY = newWrapY; }
void Grid3D::setWrapZ(bool newWrapZ) { wrapZ = newWrapZ; }
bool Grid3D::getWrapX(void) const { return wrapX; }
bool Grid3D::getWrapY(void) const { return wrapY; }
bool Grid3D::getWrapZ(void) const { return wrapZ; }

void Grid3D::setMaxX(unsigned int newMaxX) {
    maxX = newMaxX;
}

void Grid3D::setMaxY(unsigned int newMaxY) {
    maxY = newMaxY;
}

void Grid3D::setMaxZ(unsigned int newMaxZ) {
    maxZ = newMaxZ;
}

std::vector<GridCoord3D> Grid3D::getNeighborhood(AgentID agentID, GridNeighborhoodType nType, bool includeCenter) const {
    GridCoord3D location = getLocationByAgent(agentID);

    return getNeighborhood(location, nType, includeCenter);
}

std::vector<GridCoord3D> Grid3D::getNeighborhood(GridCoord3D location, GridNeighborhoodType nType, bool includeCenter) const {
    std::vector<GridCoord3D> neighborhood;
    auto x = location.getX();
    auto y = location.getY();
    auto z = location.getZ();

    if (includeCenter == true)
        neighborhood.push_back(location);

    // N, E, S, W...and so on...
    neighborhood.push_back(locationWrap(x, y, z - 1));
    neighborhood.push_back(locationWrap(x, y, z + 1));
    neighborhood.push_back(locationWrap(x, y - 1, z));
    neighborhood.push_back(locationWrap(x, y + 1, z));
    neighborhood.push_back(locationWrap(x - 1, y, z));
    neighborhood.push_back(locationWrap(x + 1, y, z));

    if (nType == GridNeighborhoodType::Moore) {
        // NE, SE, SW, NW...oh my.
        neighborhood.push_back(locationWrap(x, y - 1, z - 1));
        neighborhood.push_back(locationWrap(x, y - 1, z + 1));
        neighborhood.push_back(locationWrap(x, y + 1, z - 1));
        neighborhood.push_back(locationWrap(x, y + 1, z + 1));

        neighborhood.push_back(locationWrap(x - 1, y - 1, z - 1));
        neighborhood.push_back(locationWrap(x - 1, y - 1, z));
        neighborhood.push_back(locationWrap(x - 1, y - 1, z + 1));
        neighborhood.push_back(locationWrap(x - 1, y, z - 1));
        neighborhood.push_back(locationWrap(x - 1, y, z + 1));
        neighborhood.push_back(locationWrap(x - 1, y + 1, z - 1));
        neighborhood.push_back(locationWrap(x - 1, y + 1, z));
        neighborhood.push_back(locationWrap(x - 1, y + 1, z + 1));

        neighborhood.push_back(locationWrap(x + 1, y - 1, z - 1));
        neighborhood.push_back(locationWrap(x + 1, y - 1, z));
        neighborhood.push_back(locationWrap(x + 1, y - 1, z + 1));
        neighborhood.push_back(locationWrap(x + 1, y, z - 1));
        neighborhood.push_back(locationWrap(x + 1, y, z + 1));
        neighborhood.push_back(locationWrap(x + 1, y + 1, z - 1));
        neighborhood.push_back(locationWrap(x + 1, y + 1, z));
        neighborhood.push_back(locationWrap(x + 1, y + 1, z + 1));
    }

    return neighborhood;
}

std::vector<AgentID> *Grid3D::getCellContents(GridCoord3D location) const {
    if (isLocationValid(location)) {
        return &agentGrid[location.getX()][location.getY()][location.getZ()];
    }

    return nullptr;
}

unsigned int Grid3D::getMaxX(void) const { return maxX; }
unsigned int Grid3D::getMaxY(void) const { return maxY; }
unsigned int Grid3D::getMaxZ(void) const { return maxZ; }

GridCoord3D Grid3D::locationWrap(GridCoord3D location) const {
    return locationWrap(location.getX(), location.getY(), location.getZ());
}

GridCoord3D Grid3D::locationWrap(int x, int y, int z) const {
    if (wrapX == true)
        x = (x + static_cast<int>(maxX)) % static_cast<int>(maxX);
    if (wrapY == true)
        y = (y + static_cast<int>(maxY)) % static_cast<int>(maxY);
    if (wrapZ == true)
        z = (z + static_cast<int>(maxZ)) % static_cast<int>(maxZ);

    return GridCoord3D(x, y, z);
}

bool Grid3D::isEmpty(GridCoord3D location) const {
    auto x = location.getX();
    auto y = location.getY();
    auto z = location.getZ();

    return agentGrid[x][y][z].size() == 0;
}

}
