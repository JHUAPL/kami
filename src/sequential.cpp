/*-
 * TODO FILE HEADER
 */

#include <kami/agent.hpp>
#include <kami/model.hpp>
#include <kami/sequential.hpp>
#include <kami/scheduler.hpp>
#include <random>
#include <string>

namespace kami {

SequentialScheduler::SequentialScheduler(Model *newModel) {
    stepCounter = 0;
    model = newModel;
}

SequentialScheduler::~SequentialScheduler() {}

void SequentialScheduler::addAgent(AgentID newAgentID) {
    agentList.push_back(newAgentID);
}

void SequentialScheduler::deleteAgent(AgentID oldAgentID) {
    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        if (*agentID == oldAgentID) {
            agentList.erase(agentID);
            return;
        }
    }
    // ERROR HERE
}

void SequentialScheduler::step() {
    stepCounter++;

    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        Agent *agent = model->getAgentByID(*agentID);
        if (agent != nullptr)
            agent->step();
        // ERROR HERE
    }
}

}  // namespace kami
