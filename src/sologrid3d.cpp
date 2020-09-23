/*-
 * TODO FILEHEADER
 */

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/grid3d.hpp>
#include <kami/kami.hpp>
#include <kami/sologrid3d.hpp>

namespace kami {

SoloGrid3D::SoloGrid3D(unsigned int newMaxX, unsigned int newMaxY, unsigned int newMaxZ,
                       bool newWrapX, bool newWrapY, bool newWrapZ)
    : Grid3D(newMaxX, newMaxY, newMaxZ, newWrapX, newWrapY, newWrapZ) {}

bool SoloGrid3D::addAgent(AgentID agentID, GridCoord3D location) {
    if (isLocationValid(location) & isEmpty(location)) {
        agentIndex->insert(std::pair<AgentID, GridCoord3D>(agentID, location));
        agentGrid[location.getX()][location.getY()][location.getZ()].push_back(agentID);
        return (true);
    }

    return (false);
}

}  // namespace kami
