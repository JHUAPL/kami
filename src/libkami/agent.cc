/*-
 * TODO FILE HEADER
 */

#include <kami/agent.h>
#include <string>

namespace kami {

uint64_t AgentID::idGen = 1;

AgentID::AgentID() {
    id = idGen++;
}

std::string AgentID::toString() const {
    return std::to_string(id);
}

bool operator==(const AgentID &lhs, const AgentID &rhs) {
    return lhs.id == rhs.id;
}

bool operator!=(const AgentID &lhs, const AgentID &rhs) {
    return !(lhs == rhs);
}

bool operator<(const AgentID &lhs, const AgentID &rhs) {
    return lhs.id < rhs.id;
}

std::ostream &operator<<(std::ostream &lhs, const AgentID &rhs) {
    return lhs << rhs.toString();
}

AgentID Agent::getAgentID() const {
    return agentID;
}


bool operator==(const Agent &lhs, const Agent &rhs) {
    return lhs.agentID == rhs.agentID;
}

bool operator!=(const Agent &lhs, const Agent &rhs) {
    return !(lhs == rhs);
}

void TwoActionAgent::step() {
    stepA();
    stepB();
}

}  // namespace kami
