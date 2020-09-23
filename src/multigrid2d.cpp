/*-
 * TODO FILEHEADER
 */

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/grid2d.hpp>
#include <kami/kami.hpp>
#include <kami/multigrid2d.hpp>

namespace kami {

MultiGrid2D::MultiGrid2D(unsigned int newMaxX, unsigned int newMaxY, bool newWrapX, bool newWrapY)
    : Grid2D(newMaxX, newMaxY, newWrapX, newWrapY) {}

bool MultiGrid2D::addAgent(AgentID agentID, GridCoord2D location) {
    if (isLocationValid(location)) {
        agentIndex->insert(std::pair<AgentID, GridCoord2D>(agentID, location));
        agentGrid[location.getX()][location.getY()].push_back(agentID);
        return (true);
    }

    return (false);
}

}  // namespace kami
