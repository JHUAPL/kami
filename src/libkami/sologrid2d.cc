/*-
 * TODO FILEHEADER
 */

#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/grid2d.h>
#include <kami/kami.h>
#include <kami/sologrid2d.h>
#include <vector>

namespace kami {

SoloGrid2D::SoloGrid2D(unsigned int newMaxX, unsigned int newMaxY, bool newWrapX, bool newWrapY)
    : Grid2D(newMaxX, newMaxY, newWrapX, newWrapY) {}

bool SoloGrid2D::addAgent(AgentID agentID, GridCoord2D location) {
    if (isLocationValid(location) & isEmpty(location)) {
        agentIndex->insert(std::pair<AgentID, GridCoord2D>(agentID, location));
        agentGrid[location.getX()][location.getY()].push_back(agentID);
        return (true);
    }

    return (false);
}

}  // namespace kami
