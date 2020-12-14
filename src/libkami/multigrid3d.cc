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
#include <kami/grid3d.h>
#include <kami/kami.h>
#include <kami/multigrid3d.h>
#include <map>
#include <mutex>
#include <vector>

namespace kami {

MultiGrid3D::MultiGrid3D(unsigned int newMaxX, unsigned int newMaxY, unsigned int newMaxZ,
                         bool newWrapX, bool newWrapY, bool newWrapZ)
    : Grid3D(newMaxX, newMaxY, newMaxZ, newWrapX, newWrapY, newWrapZ) {}

bool MultiGrid3D::addAgent(AgentID agentID, GridCoord3D location) {
    if (isLocationValid(location)) {
        agentIndex->insert(std::pair<AgentID, GridCoord3D>(agentID, location));
        agentGrid[location.getX()][location.getY()][location.getZ()].push_back(agentID);
        return (true);
    }

    return (false);
}

}  // namespace kami
