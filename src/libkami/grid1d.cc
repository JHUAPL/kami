/*-
 * Copyright (c) 2020 The Johns Hopkins University Applied Physics
 * Laboratory LLC
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/grid1d.h>
#include <kami/kami.h>
#include <map>
#include <vector>

namespace kami {

GridCoord1D::GridCoord1D(int newX) {
    x = newX;
}

int GridCoord1D::getX() const {
    return x;
}

std::string GridCoord1D::toString() const {
    return std::string("(" + std::to_string(x) + ")");
}

bool operator==(const GridCoord1D &lhs, const GridCoord1D &rhs) {
    return (lhs.x == rhs.x);
}

bool operator!=(const GridCoord1D &lhs, const GridCoord1D &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &lhs, const GridCoord1D &rhs) {
    return lhs << "(" << rhs.x << ")";
}

Grid1D::Grid1D(unsigned int newMaxX, bool newWrapX = false) {
    setMaxX(newMaxX);
    setWrapX(newWrapX);

    agentGrid = new std::vector<AgentID>[maxX];
    agentIndex = new std::map<AgentID, GridCoord1D>;
}

Grid1D::~Grid1D(void) {
    delete agentIndex;
    delete[] agentGrid;
}

bool Grid1D::addAgent(AgentID agentID, int coord) {
    return addAgent(agentID, GridCoord1D(coord));
}

bool Grid1D::deleteAgent(AgentID agentID) {
    GridCoord1D location = getLocationByAgent(agentID);

    return deleteAgent(agentID, location);
}

bool Grid1D::deleteAgent(AgentID agentID, int coord) {
    return deleteAgent(agentID, GridCoord1D(coord));
}

bool Grid1D::isLocationValid(GridCoord1D location) const {
    auto x = location.getX();

    return (x >= 0 && x < static_cast<int>(maxX));
}

bool Grid1D::isEmpty(GridCoord1D location) const {
    auto x = location.getX();

    return agentGrid[x].size() == 0;
}

bool Grid1D::deleteAgent(AgentID agentID, GridCoord1D location) {
    auto agentList = agentGrid[static_cast<int>(location.getX())];

    for (auto testAgentID = agentList.begin(); testAgentID < agentList.end(); testAgentID++) {
        if (*testAgentID == agentID) {
            agentList.erase(testAgentID);
            agentIndex->erase(agentID);
            return true;
        }
    }

    return false;
}

bool Grid1D::moveAgent(AgentID agentID, GridCoord1D nextLocation) {
    GridCoord1D currLocation = getLocationByAgent(agentID);

    if (deleteAgent(agentID, currLocation) == true)
        return addAgent(agentID, nextLocation);
    return false;
}

std::vector<GridCoord1D> Grid1D::getNeighborhood(AgentID agentID, bool includeCenter) const {
    GridCoord1D currLocation = getLocationByAgent(agentID);

    return getNeighborhood(currLocation, includeCenter);
}

std::vector<GridCoord1D> Grid1D::getNeighborhood(GridCoord1D location, bool includeCenter) const {
    std::vector<GridCoord1D> neighborhood;
    auto x = location.getX();

    if (includeCenter == true)
        neighborhood.push_back(location);

    // E, W
    neighborhood.push_back(locationWrap(x + 1));
    neighborhood.push_back(locationWrap(x - 1));

    return neighborhood;
}

std::vector<AgentID> *Grid1D::getCellContents(GridCoord1D location) const {
    if (isLocationValid(location)) {
        return &agentGrid[location.getX()];
    }

    return nullptr;
}

void Grid1D::setWrapX(bool newWrapX) {
    wrapX = newWrapX;
}
bool Grid1D::getWrapX(void) const {
    return wrapX;
}

void Grid1D::setMaxX(unsigned int newMaxX)  {
    maxX = newMaxX;
}

unsigned int Grid1D::getMaxX(void) const {
    return maxX;
}

GridCoord1D Grid1D::getLocationByAgent(AgentID agentID) const {
    return agentIndex->at(agentID);
}

GridCoord1D Grid1D::locationWrap(GridCoord1D location) const {
    return locationWrap(location.getX());
}

GridCoord1D Grid1D::locationWrap(int x) const {
    if (wrapX == true)
        x = (x + static_cast<int>(maxX)) % static_cast<int>(maxX);
    return GridCoord1D(x);
}

}  // namespace kami
