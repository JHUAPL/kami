/*-
 * TODO FILE HEADER
 */

#include <kami/agent.hpp>
#include <kami/model.hpp>
#include <kami/scheduler.hpp>
#include <kami/sequential.hpp>
#include <kami/staged.hpp>
#include <random>
#include <string>

namespace kami {

StagedScheduler::StagedScheduler(Model *newModel) {
    stepCounter = 0;
    model = newModel;
}

StagedScheduler::~StagedScheduler() {}

void StagedScheduler::addAgent(AgentID newAgentID) {
    agentList.push_back(newAgentID);
}

void StagedScheduler::deleteAgent(AgentID oldAgentID) {
    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        if (*agentID == oldAgentID) {
            agentList.erase(agentID);
            return;
        }
    }
    // ERROR HERE
}

void StagedScheduler::step() {
    stepCounter++;

    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        StagedAgent *agent = dynamic_cast<StagedAgent *>(model->getAgentByID(*agentID));
        if (agent != nullptr)
            agent->preStep();
        // ERROR HERE
    }
    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        StagedAgent *agent = dynamic_cast<StagedAgent *>(model->getAgentByID(*agentID));
        if (agent != nullptr)
            agent->step();
        // ERROR HERE
    }
    for (auto agentID = agentList.begin(); agentID < agentList.end(); agentID++) {
        StagedAgent *agent = dynamic_cast<StagedAgent *>(model->getAgentByID(*agentID));
        if (agent != nullptr)
            agent->postStep();
        // ERROR HERE
    }
}

}  // namespace kami
