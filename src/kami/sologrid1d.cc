/*-
 * TODO FILEHEADER
 */

#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/grid1d.h>
#include <kami/kami.h>
#include <kami/sologrid1d.h>

namespace kami {

SoloGrid1D::SoloGrid1D(unsigned int newMaxX, bool newWrapX) : Grid1D(newMaxX, newWrapX) {}

bool SoloGrid1D::addAgent(AgentID agentID, GridCoord1D location) {
    if (isLocationValid(location) & isEmpty(location)) {
        agentIndex->insert(std::pair<AgentID, GridCoord1D>(agentID, location));
        agentGrid[location.getX()].push_back(agentID);
        return true;
    }

    return false;
}

}  // namespace kami
