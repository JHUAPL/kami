/*-
 * TODO FILEHEADER
 */

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/grid1d.hpp>
#include <kami/kami.hpp>
#include <kami/sologrid1d.hpp>

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
