/*-
 * TODO FILEHEADER
 */

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/grid3d.hpp>
#include <kami/kami.hpp>
#include <kami/multigrid3d.hpp>
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
