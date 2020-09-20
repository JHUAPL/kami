/*
 *
 */

#include "kami/random.hpp"

#include <random>
#include <string>

#include "kami/agent.hpp"
#include "kami/model.hpp"
#include "kami/scheduler.hpp"

namespace kami {

RandomScheduler::RandomScheduler(Model *newModel) {
    stepCounter = 0;
    model = newModel;
}

RandomScheduler::~RandomScheduler() {}

void RandomScheduler::addAgent(AgentID newAgentID) {
    agentList.push_back(newAgentID);
}

void RandomScheduler::deleteAgent(AgentID oldAgentID) {
    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        if (*agentID == oldAgentID) {
            agentList.erase(agentID);
            return;
        }
    }
    // ERROR HERE
}

void RandomScheduler::step() {
    stepCounter++;

    shuffle(agentList.begin(), agentList.end(), rng);
    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        Agent *agent = model->getAgentByID(*agentID);
        if (agent != nullptr)
            agent->step();
        // ERROR HERE
    }
}

}  // namespace kami
