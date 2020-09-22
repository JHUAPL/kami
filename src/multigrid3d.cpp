/*-
 * TODO FILEHEADER
 */

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/kami.hpp>
#include <kami/multigrid3d.hpp>
#include <map>
#include <mutex>
#include <vector>

namespace kami {

MultiGrid3DCoord::MultiGrid3DCoord(int newX, int newY, int newZ) {
    x = newX;
    y = newY;
    z = newZ;
}

int MultiGrid3DCoord::getX(void) const {
    return x;
}

int MultiGrid3DCoord::getY(void) const {
    return y;
}

int MultiGrid3DCoord::getZ(void) const {
    return z;
}

bool operator==(const MultiGrid3DCoord &lhs, const MultiGrid3DCoord &rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}

bool operator!=(const MultiGrid3DCoord &lhs, const MultiGrid3DCoord &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &lhs, const MultiGrid3DCoord &rhs) {
    return lhs << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
}

MultiGrid3D::MultiGrid3D(unsigned int newMaxX, unsigned int newMaxY, unsigned int newMaxZ,
                         bool newWrapX = false, bool newWrapY = false, bool newWrapZ = false) {
    maxX = newMaxX;
    maxY = newMaxY;
    maxZ = newMaxZ;

    setWrapX(newWrapX);
    setWrapY(newWrapY);
    setWrapZ(newWrapZ);

    agentGrid = new std::vector<AgentID> **[maxX];
    for (unsigned int i = 0; i < maxX; i++) {
        agentGrid[i] = new std::vector<AgentID> *[maxY];
        for (unsigned int j = 0; j < maxY; j++)
            agentGrid[i][j] = new std::vector<AgentID>[maxZ];
    }
    agentIndex = new std::map<AgentID, MultiGrid3DCoord>;
}

MultiGrid3D::~MultiGrid3D(void) {
    delete agentIndex;

    for (unsigned int i = 0; i < maxX; i++) {
        for (unsigned int j = 0; j < maxY; j++)
            delete[] agentGrid[i][j];
        delete[] agentGrid[i];
    }
    delete[] agentGrid;
}

bool MultiGrid3D::addAgent(AgentID agentID, int x, int y, int z) {
    return addAgent(agentID, MultiGrid3DCoord(x, y, z));
}

bool MultiGrid3D::addAgent(AgentID agentID, MultiGrid3DCoord location) {
    if (isLocationValid(location)) {
        agentIndex->insert(std::pair<AgentID, MultiGrid3DCoord>(agentID, location));
        agentGrid[location.getX()][location.getY()][location.getZ()].push_back(agentID);
        return true;
    }

    return false;
}

void MultiGrid3D::deleteAgent(AgentID agentID) {
    MultiGrid3DCoord location = getLocationByAgent(agentID);

    deleteAgent(agentID, location);
}

void MultiGrid3D::deleteAgent(AgentID agentID, int x, int y, int z) {
    deleteAgent(agentID, MultiGrid3DCoord(x, y, z));
}

void MultiGrid3D::deleteAgent(AgentID agentID, MultiGrid3DCoord location) {
    auto agentList = agentGrid[static_cast<int>(location.getX())][static_cast<int>(location.getY())][static_cast<int>(location.getZ())];
    for (auto testAgentID = agentList.begin(); testAgentID < agentList.end(); testAgentID++) {
        if (*testAgentID == agentID) {
            agentList.erase(testAgentID);
            agentIndex->erase(agentID);
        }
    }
}

bool MultiGrid3D::isLocationValid(MultiGrid3DCoord location) const {
    auto x = location.getX();
    auto y = location.getY();
    auto z = location.getZ();

    return (x >= 0 && x < static_cast<int>(maxX) &&
            y >= 0 && y < static_cast<int>(maxY) &&
            z >= 0 && z < static_cast<int>(maxZ));
}

MultiGrid3DCoord MultiGrid3D::getLocationByAgent(AgentID agentID) const {
    return agentIndex->at(agentID);
}

void MultiGrid3D::moveAgent(AgentID agentID, MultiGrid3DCoord nextLocation) {
    MultiGrid3DCoord currLocation = getLocationByAgent(agentID);

    deleteAgent(agentID, currLocation);
    addAgent(agentID, nextLocation);
}

void MultiGrid3D::setWrapX(bool newWrapX) { wrapX = newWrapX; }
void MultiGrid3D::setWrapY(bool newWrapY) { wrapY = newWrapY; }
void MultiGrid3D::setWrapZ(bool newWrapZ) { wrapZ = newWrapZ; }
bool MultiGrid3D::getWrapX(void) const { return wrapX; }
bool MultiGrid3D::getWrapY(void) const { return wrapY; }
bool MultiGrid3D::getWrapZ(void) const { return wrapZ; }

std::vector<MultiGrid3DCoord> MultiGrid3D::getNeighborhood(AgentID agentID, GridNeighborhoodType nType, bool includeCenter) const {
    MultiGrid3DCoord location = getLocationByAgent(agentID);

    return getNeighborhood(location, nType, includeCenter);
}

std::vector<MultiGrid3DCoord> MultiGrid3D::getNeighborhood(MultiGrid3DCoord location, GridNeighborhoodType nType, bool includeCenter) const {
    std::vector<MultiGrid3DCoord> neighborhood;
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

std::vector<AgentID> *MultiGrid3D::getCellContents(MultiGrid3DCoord location) {
    if (isLocationValid(location)) {
        return &agentGrid[location.getX()][location.getY()][location.getZ()];
    }

    return nullptr;
}

unsigned int MultiGrid3D::getMaxX(void) const { return maxX; }
unsigned int MultiGrid3D::getMaxY(void) const { return maxY; }
unsigned int MultiGrid3D::getMaxZ(void) const { return maxZ; }

MultiGrid3DCoord MultiGrid3D::locationWrap(MultiGrid3DCoord location) const {
    return locationWrap(location.getX(), location.getY(), location.getZ());
}

MultiGrid3DCoord MultiGrid3D::locationWrap(int x, int y, int z) const {
    if (wrapX == true)
        x = (x + static_cast<int>(maxX)) % static_cast<int>(maxX);
    if (wrapY == true)
        y = (y + static_cast<int>(maxY)) % static_cast<int>(maxY);
    if (wrapZ == true)
        z = (z + static_cast<int>(maxZ)) % static_cast<int>(maxZ);

    return MultiGrid3DCoord(x, y, z);
}

}  // namespace kami
